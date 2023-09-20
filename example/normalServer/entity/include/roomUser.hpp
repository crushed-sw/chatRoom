#ifndef __ROOM_USER_HPP
#define __ROOM_USER_HPP

#include "rooms.hpp"

class RoomUser : public Rooms {
public:
    RoomUser(int roomid = -1, const std::string& roomname = "", int roomuser = -1, const std::string& username = "");

    RoomUser(const std::vector<std::string>& vec);
    std::map<std::string, std::string> get() const;

    void setUsername(const std::string& username);
    std::string getUsername() const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomUser, roomid, roomname, roomuser, username);

    std::string username;
};

#endif //__ROOM_USER_HPP
