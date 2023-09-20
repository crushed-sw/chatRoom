#include "../include/rooms.hpp"

Rooms::Rooms(int roomid, const std::string& roomname, int roomuser)
        : roomid(roomid)
        , roomname(roomname)
        , roomuser(roomuser) {}

Rooms::Rooms(const std::vector<std::string>& vec) {
    roomid = std::atoi(vec[0].c_str());
    roomname = vec[1];
    roomuser = std::atoi(vec[2].c_str());
}

std::map<std::string, std::string> Rooms::get() const {
    std::map<std::string, std::string> res;
    res["roomid"] = std::to_string(roomid);
    res["roomname"] = roomname;
    res["roomuser"] = std::to_string(roomuser);
    return res;
}

void Rooms::setRoomid(int roomid) {
    this->roomid = roomid;
}

void Rooms::setRoomname(const std::string& roomname) {
    this->roomname = roomname;
}

void Rooms::setRoomuser(int roomuser) {
    this->roomuser = roomuser;
}

int Rooms::getRoomid() const {
    return roomid;
}

std::string Rooms::getRoomname() const {
    return roomname;
}

int Rooms::getRoomuser() const {
    return roomuser;
}

