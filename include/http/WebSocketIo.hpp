#ifndef __WEBSOCKETIO_HPP
#define __WEBSOCKETIO_HPP

#include "../net/Buffer.hpp"
#include "../net/TcpConnection.hpp"

namespace crushed {
namespace http {

class HttpServer;

class WebSocketIo {
public:
    struct WebSocketMessage {
        std::string data;
        bool isfinish;
        bool isping;
        bool iscontinue;
        bool isclose;
    };

    WebSocketIo(HttpServer* server, const net::TcpConnectionPtr& conn, const std::string& path);
    ~WebSocketIo();

    std::string getPath() const;
    void setPath(const std::string& str);

    void close();

    void send(const std::string& str);
    void sendFrame(const std::string& str);

    static WebSocketMessage getFrame(net::Buffer* buffer);
    static std::string setFrame(const std::string& message);

    static std::string buildPongFrame();
    static std::string buildCloseFrame();

private:
    std::string path_;
    net::TcpConnectionPtr conn_;
    HttpServer* httpServer_;
};

} // namespace http
} // namespace crushed

#endif //__WEBSOCKETIO_HPP
