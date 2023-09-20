#include "../include/rpcEntiry.hpp"

void RpcEntity::entityToRpc(int code, const std::string& msg, crushed::MysqlResultCode* result) {
    result->set_code(code);
    result->set_msg(msg);
}

void RpcEntity::rpcToEntity(const crushed::MysqlResultCode* result, int& code, std::string& msg) {
    code = result->code();
    msg = result->msg();
}

void RpcEntity::entityToRpc(const User& user, crushed::User* rpcUser) {
    rpcUser->set_userid(user.getUserid());
    rpcUser->set_username(user.getUsername());
    rpcUser->set_password(user.getPassword());
}

void RpcEntity::rpcToEntity(const crushed::User* rpcUser, User& user) {
    user.setUserid(rpcUser->userid());
    user.setUsername(rpcUser->username());
    user.setPassword(rpcUser->password());
}

void RpcEntity::entityToRpc(const Rooms& rooms, crushed::Rooms* rpcRooms) {
    rpcRooms->set_roomid(rooms.getRoomid());
    rpcRooms->set_roomname(rooms.getRoomname());
    rpcRooms->set_roomuser(rooms.getRoomuser());
}

void RpcEntity::rpcToEntity(const crushed::Rooms* rpcRooms, Rooms& rooms) {
    rooms.setRoomid(rpcRooms->roomid());
    rooms.setRoomname(rpcRooms->roomname());
    rooms.setRoomuser(rpcRooms->roomuser());
}

void RpcEntity::entityToRpc(const RoomUser& roomUser, crushed::RoomUser* rpcRoomUser) {
    rpcRoomUser->set_roomid(roomUser.getRoomid());
    rpcRoomUser->set_roomname(roomUser.getRoomname());
    rpcRoomUser->set_roomuser(roomUser.getRoomuser());
    rpcRoomUser->set_username(roomUser.getUsername());
}

void RpcEntity::rpcToEntity(const crushed::RoomUser* rpcRoomUser, RoomUser& roomUser) {
    roomUser.setRoomid(rpcRoomUser->roomuser());
    roomUser.setRoomname(rpcRoomUser->roomname());
    roomUser.setRoomuser(rpcRoomUser->roomuser());
    roomUser.setUsername(rpcRoomUser->username());
}

void RpcEntity::entityToRpc(const ChatMessage& message, crushed::ChatMessage* rpcMessage) {
    rpcMessage->set_chatid(std::atoi(message.getChatId().c_str()));
    rpcMessage->set_roomid(std::atoi(message.getRoomId().c_str()));
    rpcMessage->set_userid(std::atoi(message.getUserId().c_str()));
    rpcMessage->set_sendtime(message.getSendTime());
    rpcMessage->set_message(message.getMessage());
}

void RpcEntity::rpcToEntity(const crushed::ChatMessage* rpcMessage, ChatMessage& message) {
    message.setChatId(std::to_string(rpcMessage->chatid()));
    message.setRoomId(std::to_string(rpcMessage->roomid()));
    message.setUserId(std::to_string(rpcMessage->userid()));
    message.setSendTime(rpcMessage->sendtime());
    message.setMessage(rpcMessage->message());
}
