#ifndef __MYSQL_SERVICE_UTIL_HPP
#define __MYSQL_SERVICE_UTIL_HPP

#include "../../include/mysql.pb.h"
#include "user.hpp"
#include "rooms.hpp"
#include "roomUser.hpp"
#include "chatMessage.hpp"

class RpcEntity {
public:
    static void entityToRpc(int code, const std::string& msg, crushed::MysqlResultCode* result);
    static void rpcToEntity(const crushed::MysqlResultCode* result, int& code, std::string& msg);

    static void entityToRpc(const User& user, crushed::User* rpcUser);
    static void rpcToEntity(const crushed::User* rpcUser, User& user);

    static void entityToRpc(const Rooms& rooms, crushed::Rooms* rpcRooms);
    static void rpcToEntity(const crushed::Rooms* rpcRooms, Rooms& rooms);

    static void entityToRpc(const RoomUser& roomUser, crushed::RoomUser* rpcRoomUser);
    static void rpcToEntity(const crushed::RoomUser* rpcRoomUser, RoomUser& roomUser);

    static void entityToRpc(const ChatMessage& message, crushed::ChatMessage* rpcMessage);
    static void rpcToEntity(const crushed::ChatMessage* rpcMessage, ChatMessage& message);
};

#endif //__MYSQL_SERVICE_UTIL_HPP
