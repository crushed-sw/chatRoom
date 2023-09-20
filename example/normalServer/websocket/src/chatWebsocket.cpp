#include "../include/chatWebsocket.hpp"

void ChatWebSocket::chatOnOpen(crushed::http::WebSocketIoPtr& io) {
    WebSocketUtil::setChatWebSocket(io);
    const std::set<std::pair<std::string, std::string>>& socketSet = WebSocketUtil::getOnlineWebSocket(io);
    Message<std::set<std::pair<std::string, std::string>>> message(Codes::GetOk, socketSet, "");
    notifyAll(io, message.parse());
}

void ChatWebSocket::chatOnMessage(crushed::http::WebSocketIoPtr& io, const std::string& str) {
    nlohmann::json json = nlohmann::json::parse(str);
    std::string token = json["token"];

    try {
        if(!TokenUtil::checkToken(token, StringUtil::getUserIdFromChatPath(io->getPath()))) {
            Message<std::string> message(Codes::TokenError, "", "");
            io->send(message.parse());
        }
    } catch(std::exception e) {
        Message<std::string> message(Codes::TokenError, "", "");
        io->send(message.parse());
    }

    if(json["cause"] == "sendmessage") {
        Message<std::string> message(Codes::Message, str, "");

        notifyAll(io, message.parse());
        ChatMessage chatMessage;
        from_json(json, chatMessage);

        chatService_.insert(chatMessage);
    } else if(json["cause"] == "deleteroom") {
        std::string userid = json["userid"];
        std::string roomid = json["roomid"];
        
        Rooms room = roomService_.query(std::atoi(roomid.c_str()));
        if(room.getRoomuser() != std::atoi(userid.c_str())) {
            Message<std::string> message(Codes::DeleteError, "", "您不是房主，删除失败");
            io->send(message.parse());
        } else {
            roomService_.remove(std::atoi(roomid.c_str()));
            WebSocketUtil::notifyAllRooms();
            Message<std::string> message(Codes::DeleteOk, "", "");
            notifyAll(io, message.parse());
            WebSocketUtil::removeChatRoomWebSocket("/" + roomid);
        }
    }
}

void ChatWebSocket::chatOnClose(crushed::http::WebSocketIoPtr& io) {
    WebSocketUtil::removeChatWebSocket(io);
    const std::set<std::pair<std::string, std::string>>& socketSet = WebSocketUtil::getOnlineWebSocket(io);
    Message<std::set<std::pair<std::string, std::string>>> message(Codes::GetOk, socketSet, "");

    notifyAll(io, message.parse());
}

void ChatWebSocket::notifyAll(crushed::http::WebSocketIoPtr& io, const std::string& str) {
    auto& allUser = WebSocketUtil::getChatWebSocket(io);

    for(auto& user : allUser) {
        user->send(str);
    }
}

