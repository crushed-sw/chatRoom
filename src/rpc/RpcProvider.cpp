#include "../../include/rpc/RpcProvider.hpp"

using namespace crushed::rpc;

void RpcProvider::notifyService(google::protobuf::Service* service) {
    ServerInfo info;

    const google::protobuf::ServiceDescriptor* serverDesc = service->GetDescriptor();
    std::string serverName = serverDesc->name();
    int methodCount = serverDesc->method_count();

    info.server_ = service;
    for(int i = 0; i != methodCount; ++i) {
        const google::protobuf::MethodDescriptor* methodDesc = serverDesc->method(i);
        std::string methodName = methodDesc->name();
        info.methodMap_.insert({methodName, methodDesc});
    }

    serverMap_.insert({serverName, info});
}

void RpcProvider::run() {
    std::string ip = net::ServerApplication::getConfig().getValue("rpc_server_ip");
    int port = std::atoi(net::ServerApplication::getConfig().getValue("rpc_server_port").c_str());
    net::InetAddress address(port, ip);

    net::TcpServer tcpServer(&eventLoop_, address, "RpcProvider");
    tcpServer.setThreadNum(std::thread::hardware_concurrency());

    tcpServer.setConnectionCallback(std::bind(&RpcProvider::onConntion, this, std::placeholders::_1));
    tcpServer.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    tcpServer.setCloseCallback(std::bind(&RpcProvider::onClose, this, std::placeholders::_1));

    LogInfo << "rpcProvider start service at " << address.getIpPort() << LogEnd;

    tcpServer.start();
    eventLoop_.loop();
}

void RpcProvider::onClose(const net::TcpConnectionPtr& conn) {

}

void RpcProvider::onConntion(const net::TcpConnectionPtr& conn) {
    if(!conn->connected()) {
        conn->shutdown();
    }
}

void RpcProvider::onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buf, net::Timer time) {
    std::string str = buf->retrieveAllAsString();
    uint32_t headerSize = 0;
    str.copy((char*)&headerSize, 4, 0);

    std::string headerStr = str.substr(4, headerSize);
    ::rpc::RpcHeader rpcHeader;

    std::string serviceName;
    std::string methodName;
    uint32_t argsSize;

    if(rpcHeader.ParseFromString(headerStr)) {
        serviceName = rpcHeader.servicename();
        methodName = rpcHeader.methodname();
        argsSize = rpcHeader.argssize();
    } else {
        LogError << "rpcHeader: " << headerStr << " error!" << LogEnd;
        return;
    }

    std::string argsStr = str.substr(4 + headerSize, argsSize);

    auto iter = serverMap_.find(serviceName);
    if(iter == serverMap_.end()) {
        LogError << "serviceName: " << serviceName << " not excited!" << LogEnd;
        return;
    }

    google::protobuf::Service* service = iter->second.server_;

    auto methodIter = iter->second.methodMap_.find(methodName);
    if(methodIter == iter->second.methodMap_.end()) {
        LogError << "methodName: "  << methodName << " not excited!" << LogEnd;
        return;
    }

    const google::protobuf::MethodDescriptor* methodDesc = methodIter->second;

    google::protobuf::Message* request = service->GetRequestPrototype(methodDesc).New();
    if(!request->ParseFromString(argsStr)) {
        LogError << "request parse " << argsStr << " error" << LogEnd;
        return;
    }

    google::protobuf::Message* response = service->GetResponsePrototype(methodDesc).New();

    google::protobuf::Closure* done = google::protobuf::NewCallback<RpcProvider, const net::TcpConnectionPtr&, google::protobuf::Message*>
                                                                    (this, &RpcProvider::sendRpcResponse, conn, response);

    service->CallMethod(methodDesc, nullptr, request, response, done);
}

void RpcProvider::sendRpcResponse(const net::TcpConnectionPtr& conn, google::protobuf::Message* message) {
    std::string sendStr;
    if(message->SerializeToString(&sendStr)) {
        conn->send(sendStr);
    } else {
        LogError << "serialize response error" << LogEnd;
    }
    conn->shutdown();
}
