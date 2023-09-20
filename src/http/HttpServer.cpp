#include "../../include/http/HttpServer.hpp"
#include "../../include/net/Log.hpp"

#include <cstring>
#include <bitset>

#include <iconv.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include <cryptopp/sha.h>
#include <cryptopp/base64.h>

using namespace std::placeholders;
using namespace crushed::http;

static std::string calculateSecWebSocketAccept(const std::string& secWebSocketKey) {
    const std::string magicString = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string combinedString = secWebSocketKey + magicString;

    CryptoPP::SHA1 sha1;
    CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];
    sha1.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(combinedString.c_str()), combinedString.length());

    std::string base64Encoded;
    CryptoPP::Base64Encoder encoder;
    encoder.Attach(new CryptoPP::StringSink(base64Encoded));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return base64Encoded;
}

HttpServer::HttpServer(int port, int threadNum, uint32_t listenEvent,  uint32_t connEvent) 
        : port_(port)
        , threadNum_(threadNum) {

    net::ServerConfig conf = net::ServerApplication::getInstance().getConfig();
    resourceIp_ = conf.getValue("resource_ip");
    resourcePort_ = std::atoi(conf.getValue("resource_port").c_str());
}

HttpServer::HttpServer() {
    net::ServerConfig conf = net::ServerApplication::getInstance().getConfig();
    std::string port = conf.getValue("server_port");
    std::string threadNum = conf.getValue("server_threadnum");

    if(port == "") {
        port = "9999";
    }
    port_ = atoi(port.c_str());

    if(threadNum == "") {
        threadNum = std::thread::hardware_concurrency();
    }
    threadNum_ = atoi(threadNum.c_str());

    resourceIp_ = conf.getValue("resource_ip");
    resourcePort_ = std::atoi(conf.getValue("resource_port").c_str());
}

void HttpServer::addInterceptor(const interceptorTask& task) {
    interceptor_.push_back(task);
}

void HttpServer::addInterceptorPath(const std::string& interceptorPath) {
    interceptorPath_.insert(interceptorPath);
}

void HttpServer::addWebScoket(const std::string& websocketPath, const WebSocket& websocket) {
    websocketCallBack_.insert({websocketPath, websocket});
}

void HttpServer::setCallBack(const std::string& path, Request::Method method, const httpTask& callBack) {
    callBack_[path][method] = callBack;
}

void HttpServer::start() {
    net::InetAddress address(port_);
    net::TcpServer server(&loop_, address, "httpserver");
    server.setThreadNum(threadNum_);

    logInit();

    server.setConnectionCallback(std::bind(&HttpServer::connection, this, _1));
    server.setMessageCallback(std::bind(&HttpServer::message, this, _1, _2, _3));
    server.setCloseCallback(std::bind(&HttpServer::closeConn, this, _1));

    server.start();
    loop_.loop();
}

void HttpServer::connection(const net::TcpConnectionPtr& conn) {
    if(!conn->connected()) {
        conn->shutdown();
    } else {
        LogInfo << "client " << conn->peerAddress().getIpPort() << " connectd" << LogEnd;
    }
}

void HttpServer::closeWebSocketConn(const net::TcpConnectionPtr& conn) {
    std::string peeraddress = conn->peerAddress().getIpPort();
    websocketSet_[peeraddress].getOnClose()(wsConns_[peeraddress]);

    closeConn(conn);
}

void HttpServer::closeConn(const net::TcpConnectionPtr& conn) {
    std::string peeraddress = conn->peerAddress().getIpPort();
    wsConns_.erase(peeraddress);
    websocketSet_.erase(peeraddress);

    if(conn->connected()) {
        conn->shutdown();
        LogInfo << "client " << conn->peerAddress().getIpPort() << " exception closed" << LogEnd;
    } else {
        LogInfo << "client " << conn->peerAddress().getIpPort() << " would closed" << LogEnd;
    }
}

void HttpServer::message(const net::TcpConnectionPtr& conn, net::Buffer* buffer, net::Timer timer) {
    auto iter = wsConns_.find(conn->peerAddress().getIpPort());
    if(iter != wsConns_.end()) {
        solveWebSocketMessage(conn, buffer, iter);
        return;
    }

    Request request(buffer);
    Response response;

    if(request.getHeader()["Connection"].find("Upgrade") != -1 && request.getHeader()["Upgrade"].find("websocket") != -1) {
        WebSocket websocket;
        if(solveWebSocket(request, response, websocket)) {
            std::string peeraddress = conn->peerAddress().getIpPort();
            wsConns_.insert({peeraddress, std::make_shared<WebSocketIo>(this, conn, request.getPath())});
            websocketSet_.insert({peeraddress, websocket});

            conn->send(response.getMessage());
            websocketSet_[peeraddress].getOnOpen()(wsConns_[peeraddress]);
        } else {
            conn->send(response.getMessage());
        }
    } else {
        solveHttp(request, response);

        LogInfo << conn->peerAddress().getIpPort() << " get source " << request.getPath() << LogEnd;
        response.setHeader("Connection", "close");
        conn->send(response.getMessage());
        conn->shutdown();
    }
}

void HttpServer::solveWebSocketMessage(const crushed::net::TcpConnectionPtr& conn, 
                                       net::Buffer* buffer,
                                       const std::unordered_map<std::string, WebSocketIoPtr>::iterator& iter) {
    WebSocketIo::WebSocketMessage message = WebSocketIo::getFrame(buffer);

    if(message.isping && message.isfinish) {
        iter->second->sendFrame(WebSocketIo::buildPongFrame());
        return;
    }

    if(message.isclose) {
        iter->second->sendFrame(WebSocketIo::buildCloseFrame());
        closeWebSocketConn(conn);
        return;
    }

    std::string finishStr = message.data;
    while(message.iscontinue && !message.isfinish) {
        message = WebSocketIo::getFrame(buffer);
        finishStr += message.data;
    }

    websocketSet_[conn->peerAddress().getIpPort()].getOnMessage()(iter->second, finishStr);
}

bool HttpServer::solveWebSocket(Request& request, Response& response, WebSocket& websocket) {
    std::string path = request.getPath();

    if(checkWebsocketPath(path, websocket)) { 
        std::string secWebSocketAccept = calculateSecWebSocketAccept(request.getHeader()["Sec-WebSocket-Key"]);
        secWebSocketAccept.pop_back();
        response.setCode(101, "Switching Protocols");

        response.setHeader("Upgrade", "websocket");
        response.setHeader("Connection", "Upgrade");
        response.setHeader("Sec-WebSocket-Accept", secWebSocketAccept);
        response.setHeader("WebSocket-Location", "ws://" + request.getHeader()["Host"]);
        return true;
    } else {
        response.setCode(400, "Bad Request");
        return false;
    }
}

void HttpServer::solveHttp(Request& request, Response& response) {
    if(interceptorPath_.find(request.getPath()) != interceptorPath_.end()) {
        for(auto interceptor : interceptor_) {
            if(!interceptor(request, response)) {
                return;
            }
        }
    }

    Request::Method method = request.getMethod();
    std::string path = request.getPath();

    auto pathIter = callBack_.find(path);
    if(pathIter != callBack_.end()) {
        auto methodIter = pathIter->second.find(method);
        if(methodIter != pathIter->second.end()) {
            response.setHeader("Content-Type", "application/json");
            std::string jsonContent = callBack_[path][method](request, response);
            response.setHeader("Content-Length", std::to_string(jsonContent.length()));
            response.addContent(jsonContent);
            return;
        }
    }

    crushed::ResourceService_Stub stub(new rpc::RpcChannel(resourceIp_, resourcePort_));
    rpc::RpcController controller;

    ResourceRequest resourceRequest;
    ResourceResponse resourceResponse;
    resourceRequest.set_path(path);

    stub.getResource(&controller, &resourceRequest, &resourceResponse, nullptr);
    if(!controller.Failed()) {
        response.setCode(resourceResponse.result().code(), resourceResponse.result().msg());
        response.setHeader("Content-Type", resourceResponse.result().type());

        std::string content = resourceResponse.responsemessage();
        response.setHeader("Content-Length", std::to_string(content.length()));
        response.addContent(content);
    } else {
        response.setCode(500, "Internal Server Error");
    }
}

void HttpServer::logInit() {
    LogInfo << "==================== Server Init  ====================" << LogEnd;
    LogInfo << "Port: " << port_ << ", threadNum: " << threadNum_ << LogEnd;
    LogInfo << "Resource server: " << resourceIp_ << ":" << resourcePort_ << LogEnd;
    LogInfo << "==================== Server Start ====================" << LogEnd;
}

std::vector<std::string> HttpServer::splitString(const std::string& str) {
    std::vector<std::string> ans;

    auto slow = str.begin();
    auto fast = str.begin();
    while(fast != str.end()) {
        if(*fast == '/' && fast != slow) {
            ans.emplace_back(slow, fast);
            slow = fast;
        }
        fast++;
    }
    ans.emplace_back(slow, fast);

    return ans;
}

bool HttpServer::checkWebsocketPath(const std::string& str, WebSocket& websocket) {
    std::vector<std::string> path = splitString(str);

    for(auto callbackPath : websocketCallBack_) {
        std::vector<std::string> alreadyPath = splitString(callbackPath.first);
        if(path.size() == alreadyPath.size()) {
            bool isTrue = true;
            for(int i = 0; i != path.size(); ++i) {
                if(alreadyPath[i] != "/{}" && path[i] != alreadyPath[i]) {
                    isTrue = false;
                    break;
                }
            }
            if(isTrue) {
                websocket = callbackPath.second;
                return true;
            }
        }
    }

    return false;
}
