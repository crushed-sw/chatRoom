#include "../../include/http/WebSocket.hpp"
#include "../../include/net/TcpServer.hpp"

using namespace crushed::http;
using namespace std::placeholders;

WebSocket::WebSocket() 
        : onOpen_(std::bind(&WebSocket::onOpen, this, _1))
        , onClose_(std::bind(&WebSocket::onClose, this, _1))
        , onMessage_(std::bind(&WebSocket::onMessage, this, _1, _2))
        , onError_(std::bind(&WebSocket::onError, this, _1))
{}

WebSocket::~WebSocket() {}

void WebSocket::setOnOpen(const webSocketCallback& cb) {
    onOpen_ = cb;
}

void WebSocket::setOnMessage(const webSocketMessageCallback& cb) {
    onMessage_ = cb;
}

void WebSocket::setOnClose(const webSocketCallback& cb) {
    onClose_ = cb;
}

void WebSocket::setOnError(const webSocketCallback& cb) {
    onError_ = cb;
}

WebSocket::webSocketCallback& WebSocket::getOnOpen() {
    return onOpen_;
}

WebSocket::webSocketMessageCallback& WebSocket::getOnMessage() {
    return onMessage_;
}

WebSocket::webSocketCallback& WebSocket::getOnClose() {
    return onClose_;
}

WebSocket::webSocketCallback& WebSocket::getOnError() {
    return onError_;
}

void WebSocket::onOpen(WebSocketIoPtr& webSocketIo) {}

void WebSocket::onMessage(WebSocketIoPtr& webSocketIo, const std::string& str) {}

void WebSocket::onClose(WebSocketIoPtr& webSocketIo) {}

void WebSocket::onError(WebSocketIoPtr& webSocketIo) {}

