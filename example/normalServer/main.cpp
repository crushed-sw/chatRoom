#include "../../include/net/ServerApplication.hpp"
#include "../../include/http/HttpServer.hpp"

#include "controller/include/loginController.hpp"
#include "controller/include/tokenInterceptor.hpp"

#include "websocket/include/chatWebsocket.hpp"
#include "websocket/include/roomsWebsocket.hpp"

#include <functional>
#include <iostream>

using namespace std::placeholders;

int main(int argc, char** argv) {
    crushed::net::ServerApplication::init(argc, argv);

    crushed::http::HttpServer server;

    LoginController loginController;
    server.setCallBack("/checklogin", crushed::http::Request::POST, std::bind(&LoginController::checkLogin, loginController, _1, _2));
    server.setCallBack("/login", crushed::http::Request::POST, std::bind(&LoginController::login, loginController, _1, _2));
    server.setCallBack("/register", crushed::http::Request::POST, std::bind(&LoginController::registe, loginController, _1, _2));

    crushed::http::WebSocket roomsWebsocketPath;
    RoomsWebSocket roomWebSocket;
    roomsWebsocketPath.setOnOpen(std::bind(&RoomsWebSocket::roomOnOpen, roomWebSocket, _1));
    roomsWebsocketPath.setOnMessage(std::bind(&RoomsWebSocket::roomOnMessage, roomWebSocket, _1, _2));
    roomsWebsocketPath.setOnClose(std::bind(&RoomsWebSocket::roomOnClose, roomWebSocket, _1));

    crushed::http::WebSocket chatWebsocketPath;
    ChatWebSocket chatWebSocket;
    chatWebsocketPath.setOnOpen(std::bind(&ChatWebSocket::chatOnOpen, chatWebSocket, _1));
    chatWebsocketPath.setOnMessage(std::bind(&ChatWebSocket::chatOnMessage, chatWebSocket, _1, _2));
    chatWebsocketPath.setOnClose(std::bind(&ChatWebSocket::chatOnClose, chatWebSocket, _1));

    server.addWebScoket("/rooms/{}", roomsWebsocketPath);
    server.addWebScoket("/chat/{}/{}/{}", chatWebsocketPath);

    server.start();
}
