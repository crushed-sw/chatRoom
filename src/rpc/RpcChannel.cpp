#include "../../include/rpc/RpcChannel.hpp"

using namespace crushed::rpc;

RpcChannel::RpcChannel() {
    ip_ = net::ServerApplication::getConfig().getValue("rpc_client_ip");
    port_ = std::atoi(net::ServerApplication::getConfig().getValue("rpc_client_port").c_str());
}

RpcChannel::RpcChannel(const std::string& ip, int port) : ip_(ip), port_(port) {}

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method, 
                            google::protobuf::RpcController* controller, 
                            const google::protobuf::Message* request, 
                            google::protobuf::Message* response, 
                            google::protobuf::Closure* done) {

    const google::protobuf::ServiceDescriptor* serviceDesc = method->service();
    std::string serviceName = serviceDesc->name();
    std::string methodName = method->name();

    uint32_t argSize = 0;
    std::string argsList;
    if(request->SerializeToString(&argsList)) {
        argSize = argsList.size();
    } else {
        std::string errmsg = "request serialize error";
        LogError << errmsg << LogEnd;
        controller->SetFailed(errmsg);
        return;
    }

    ::rpc::RpcHeader header;
    header.set_servicename(serviceName);
    header.set_methodname(methodName);
    header.set_argssize(argSize);

    uint32_t headerSize = 0;
    std::string headerStr;
    if(header.SerializeToString(&headerStr)) {
        headerSize = headerStr.size();
    } else {
        std::string errmsg = "headerStr serialize error";
        LogError << errmsg << LogEnd;
        controller->SetFailed(errmsg);
        return;
    }

    std::string sendRpcStr;
    sendRpcStr.insert(0, std::string((char*)&headerSize, 4));
    sendRpcStr += headerStr;
    sendRpcStr += argsList;

    net::InetAddress address(port_, ip_);

    net::EventLoop loop;
    net::TcpClient client(&loop, address, "RpcConstmer");
    client.setConnectionCallback(std::bind(&RpcChannel::onConntion, this, std::placeholders::_1, sendRpcStr));
    client.setMessageCallback(std::bind(&RpcChannel::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, response, &loop, controller));

    client.connect();
    loop.loop();
}


void RpcChannel::setIp(const std::string& ip) {
    ip_ = ip;
}

void RpcChannel::setPort(int port) {
    port_ = port;
}

std::string RpcChannel::getIP() {
    return ip_;
}

int RpcChannel::getPort() {
    return port_;
}

void RpcChannel::onConntion(const net::TcpConnectionPtr& conn, const std::string& str) {
    if(!conn->connected()) {
        conn->shutdown();
        return;
    }

    conn->send(str);
}

void RpcChannel::onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buf, net::Timer time, 
                           google::protobuf::Message*& response, net::EventLoop* loop, google::protobuf::RpcController* controller) {
    std::string str = buf->retrieveAllAsString();
    if(!response->ParseFromString(str)) {
        std::string errmsg = "parse error";
        LogError << errmsg << LogEnd;
        controller->SetFailed(errmsg);
    }

    loop->quit();
}
