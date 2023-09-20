#ifndef __ROOM_SERVICE_HPP
#define __ROOM_SERVICE_HPP

#include "../../../../include/net/Log.hpp"
#include "../../../../include/rpc/RpcChannel.hpp"
#include "../../../../include/rpc/RpcController.hpp"
#include "../../../../include/net/ServerApplication.hpp"

#include "../../entity/include/mysql.pb.h"
#include "../../entity/include/rpcEntiry.hpp"

class RoomService {
public:
    RoomService();
    ~RoomService();

    Rooms query(int roomid);
    RoomUser queryByName(int roomid);
    Rooms query(const std::string& roomname, int userid);
    void insert(const Rooms& rooms);
    void remove(int roomid);
    std::vector<Rooms> queryAll();
    std::vector<RoomUser> queryAllByName();

private:
    std::string ip_;
    int port_;
};

#endif //__USER_SERVICE_HPP
