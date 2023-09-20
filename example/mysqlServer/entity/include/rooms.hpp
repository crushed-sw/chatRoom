#ifndef __ROOMS_HPP
#define __ROOMS_HPP

#include "../../../../thirdparty/json.hpp"

#include <string>
#include <vector>
#include <map>

class Rooms {
public:
    Rooms(int roomid = -1, const std::string& roomname = "", int roomuser = -1);

    Rooms(const std::vector<std::string>& vec);
    std::map<std::string, std::string> get() const;

    void setRoomid(int roomid);
    void setRoomname(const std::string& roomname);
    void setRoomuser(int roomuser);

    int getRoomid() const;
    std::string getRoomname() const;
    int getRoomuser() const;

protected:
    int roomid;
    std::string roomname;
    int roomuser;
};

#endif //__ROOMS_HPP
