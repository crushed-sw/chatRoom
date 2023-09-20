#include "../include/user.hpp"

User::User(int userid, const std::string& username, const std::string& password) 
        : userid(userid)
        , username(username)
        , password(password) {}

User::User(const std::vector<std::string>& vec) {
    userid = std::atoi(vec[0].c_str());
    username = vec[1];
    password = vec[2];
}

std::map<std::string, std::string> User::get() const {
    std::map<std::string, std::string> res;
    res["userid"] = std::to_string(userid);
    res["username"] = username;
    res["password"] = password;
    return res;
}

void User::setUserid(int userid) {
    this->userid = userid;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

int User::getUserid() const {
    return userid;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

