#ifndef __ROOMS_MAPPER_HPP
#define __ROOMS_MAPPER_HPP

#include "../../../include/mysql/MySql.hpp"
#include "../../../include/mysql/MySqlConn.hpp"

#include "../entity/include/rooms.hpp"
#include "../entity/include/roomUser.hpp"

class RoomsMapping {
public:
    Rooms query(int roomid);
    RoomUser queryByName(int roomid);
    Rooms query(const std::string& roomname, int userid);
    void insert(const Rooms& room);
    void remove(int roomid);
    std::vector<Rooms> queryAll();
    std::vector<RoomUser> queryAllByName();
};

#endif //__ROOMS_MAPPER_HPP
