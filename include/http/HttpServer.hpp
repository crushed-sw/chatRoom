#ifndef __HTTP_SERVER_HPP
#define __HTTP_SERVER_HPP

#include "../net/ServerApplication.hpp"
#include "../net/Buffer.hpp"
#include "../net/TcpServer.hpp"
#include "../rpc/RpcChannel.hpp"
#include "../rpc/RpcController.hpp"

#include "Request.hpp"
#include "Response.hpp"
#include "WebSocket.hpp"
#include "WebSocketIo.hpp"
#include "resource.pb.h"

#include <set>
#include <string>
#include <fstream>
#include <functional>
#include <unordered_set>

namespace crushed {
namespace http {

class HttpServer {
public:
    using httpTask = std::function<std::string(Request& request, Response& response)>;
    using interceptorTask = std::function<bool(Request& request, Response& response)>;

    HttpServer(int port, int threadNum, uint32_t listenEvent, uint32_t connEvent);
    HttpServer();

    void addInterceptor(const interceptorTask& interceptor);
    void addInterceptorPath(const std::string& interceptorPath);

    void addWebScoket(const std::string& websocketPath, const WebSocket& websocket);

    void setCallBack(const std::string& path, Request::Method method, const httpTask& callBack);
    void setWebsocketCallBack(const std::string& path);

    void start();

    void closeConn(const net::TcpConnectionPtr& conn);
    void closeWebSocketConn(const net::TcpConnectionPtr& conn);

    static const int MAX_RECV_LEN = 2048;

private:
    bool solveWebSocket(Request& request, Response& response, WebSocket& websocket);
    void solveWebSocketMessage(const crushed::net::TcpConnectionPtr& conn, 
                               net::Buffer* buffer,
                               const std::unordered_map<std::string, WebSocketIoPtr>::iterator& iter);
    void solveHttp(Request& request, Response& response);

    void connection(const net::TcpConnectionPtr& conn);
    void message(const net::TcpConnectionPtr& conn, net::Buffer* buffer, net::Timer timer);

    void logInit();

    std::vector<std::string> splitString(const std::string& str);
    bool checkWebsocketPath(const std::string& str, WebSocket& websocket);

    int port_;
    int threadNum_;

    net::EventLoop loop_;

    std::unordered_map<std::string, WebSocketIoPtr> wsConns_;

    char buffer_[MAX_RECV_LEN];
    std::stringstream ss_;

    std::vector<interceptorTask> interceptor_;
    std::set<std::string> interceptorPath_;

    std::unordered_map<std::string, std::unordered_map<Request::Method, httpTask>> callBack_;
    std::unordered_map<std::string, WebSocket> websocketCallBack_;
    std::unordered_map<std::string, WebSocket> websocketSet_;

    std::unordered_map<int, std::string> ipAddress_;

    std::string resourceIp_;
    int resourcePort_;
};

} // namespace http
} // namespace crushed

#endif //__HTTP_SERVER_HPP
