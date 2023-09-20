#ifndef __WEB_SOCKET_HPP
#define __WEB_SOCKET_HPP

#include "../net/TcpServer.hpp"
#include "WebSocketIo.hpp"

#include <unordered_map>

namespace crushed {
namespace http {

using WebSocketIoPtr = std::shared_ptr<WebSocketIo>;

class WebSocket {
public:
    using webSocketCallback = std::function<void(WebSocketIoPtr&)>;
    using webSocketMessageCallback = std::function<void(WebSocketIoPtr&, const std::string&)>;

    WebSocket();
    ~WebSocket();

    void setOnOpen(const webSocketCallback& cb);
    void setOnMessage(const webSocketMessageCallback& cb);
    void setOnClose(const webSocketCallback& cb);
    void setOnError(const webSocketCallback& cb);

    webSocketCallback& getOnOpen();
    webSocketMessageCallback& getOnMessage();
    webSocketCallback& getOnClose();
    webSocketCallback& getOnError();

private:
    void onOpen(WebSocketIoPtr& webSocketIo);
    void onMessage(WebSocketIoPtr& webSocketIo, const std::string& str);
    void onClose(WebSocketIoPtr& webSocketIo);
    void onError(WebSocketIoPtr& webSocketIo);

    webSocketCallback onOpen_;
    webSocketMessageCallback onMessage_;
    webSocketCallback onClose_;
    webSocketCallback onError_;
};

} // namespace http
} // namespace crushed

#endif // __WEB_SOCKET_HPP
