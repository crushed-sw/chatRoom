#include "../include/roomsMapping.hpp"

Rooms RoomsMapping::query(int roomid) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    return mysql->queryById<Rooms>("roomid", roomid);
}

Rooms RoomsMapping::query(const std::string& roomname, int userid) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    std::stringstream ss;
    ss << "select * from rooms where roomname = ? and roomuser = ? order by roomid desc limit 1";
    return mysql->query(ss.str()).bind({roomname, std::to_string(userid)}).executeQueryOne<Rooms>();
}

void RoomsMapping::insert(const Rooms& room) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    mysql->insert(room, "roomid");
}

void RoomsMapping::remove(int roomid) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    std::stringstream ss;
    ss << "update rooms set isdelete = true where roomid = ?";
    mysql->query(ss.str()).bind({std::to_string(roomid)}).executeUpdate();
}

std::vector<Rooms> RoomsMapping::queryAll() {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    std::stringstream ss;
    ss << "select * from rooms where isdelete = false";
    return mysql->query(ss.str()).executeQuery<Rooms>();
}

RoomUser RoomsMapping::queryByName(int roomid) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    std::stringstream ss;
    ss << "select roomid, roomname, roomuser, username from user join rooms on userid = roomuser where isdelete = false and roomid = ?";
    return mysql->query(ss.str()).bind({std::to_string(roomid)}).executeQueryOne<RoomUser>();
}

std::vector<RoomUser> RoomsMapping::queryAllByName() {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "rooms");

    std::stringstream ss;
    ss << "select roomid, roomname, roomuser, username from user join rooms on userid = roomuser where isdelete = false";
    return mysql->query(ss.str()).executeQuery<RoomUser>();
}
