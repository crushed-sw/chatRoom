#ifndef __USER_HPP
#define __USER_HPP

#include "../../../../thirdparty/json.hpp"

#include <string>
#include <vector>
#include <map>

class User {
public:
    User(int userid = -1, const std::string& username = "", const std::string& password = "");

    User(const std::vector<std::string>& vec);
    std::map<std::string, std::string> get() const;

    void setUserid(int userid);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setToken(const std::string& token);

    int getUserid() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getToken() const;

private:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, userid, username, password, token);

    int userid;
    std::string username;
    std::string password;
    std::string token;
};

#endif //__USER_HPP
