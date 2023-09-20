#include "../include/roomUser.hpp"

RoomUser::RoomUser(int roomid, const std::string& roomname, int roomuser, const std::string& username)
        : Rooms(roomid, roomname, roomuser)
        , username(username) {}

RoomUser::RoomUser(const std::vector<std::string>& vec) : Rooms(vec) {
    username = vec[3];
}

std::map<std::string, std::string> RoomUser::get() const {
    auto m = Rooms::get();
    m["username"] = username;
    return m;
}

void RoomUser::setUsername(const std::string& username) {
    this->username = username;
}

std::string RoomUser::getUsername() const {
    return username;
}
