#include "../include/roomsWebsocket.hpp"

void RoomsWebSocket::roomOnOpen(crushed::http::WebSocketIoPtr& io) {
    WebSocketUtil::setRoomsWebSocket(io);

    Message<std::vector<RoomUser>> message(Codes::GetOk, service_.queryAllByName(), "");
    io->send(message.parse());
}

void RoomsWebSocket::roomOnMessage(crushed::http::WebSocketIoPtr& io, const std::string& str) {
    nlohmann::json json = nlohmann::json::parse(str);
    std::string token = json["token"];

    try {
        if(!TokenUtil::checkToken(token, StringUtil::getUserIdFromRoomPath(io->getPath()))) {
            Message<std::string> message(Codes::TokenError, "", "");
            io->send(message.parse());
        }
    } catch(std::exception e) {
        Message<std::string> message(Codes::TokenError, "", "");
        io->send(message.parse());
    }

    if(json["cause"] == "addroom") {
        std::string roomname = json["roomname"];
        std::string userid = json["userid"];

        Rooms room(-1, roomname, std::atoi(userid.c_str()));
        service_.insert(room);
        room = service_.query(roomname, std::atoi(userid.c_str()));

        WebSocketUtil::notifyAllRooms();
    }
}

void RoomsWebSocket::roomOnClose(crushed::http::WebSocketIoPtr& io) {
    WebSocketUtil::removeRoomsWebSocket(io);
}

