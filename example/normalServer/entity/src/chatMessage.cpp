#include "../include/chatMessage.hpp"

ChatMessage::ChatMessage(const std::string& chatid, const std::string& roomid, const std::string& userid,
                         const std::string& sendtime, const std::string& message)
        : chatid(chatid)
        , roomid(roomid)
        , userid(userid)
        , sendtime(sendtime)
        , message(message) {}

ChatMessage::ChatMessage(const std::vector<std::string>& vec) {
    chatid = std::atoi(vec[0].c_str());
    roomid = std::atoi(vec[1].c_str());
    userid = std::atoi(vec[2].c_str());
    sendtime = vec[3];
    message = vec[4];
}

std::map<std::string, std::string> ChatMessage::get() const {
    std::map<std::string, std::string> res;
    res["chatid"] = chatid;
    res["roomid"] = roomid;
    res["userid"] = userid;
    res["sendtime"] = sendtime;
    res["message"] = message;
    return res;
}

void ChatMessage::setChatId(const std::string& chatid) {
    this->chatid = chatid;
}

void ChatMessage::setRoomId(const std::string& roomid) {
    this->roomid = roomid;
}

void ChatMessage::setUserId(const std::string& userid) {
    this->userid = userid;
}

void ChatMessage::setSendTime(const std::string& sendtime) {
    this->sendtime = sendtime;
}

void ChatMessage::setMessage(const std::string& message) {
    this->message = message;
}

void ChatMessage::setUsername(const std::string& username) {
    this->username = username;
}

std::string ChatMessage::getChatId() const {
    return chatid;
}

std::string ChatMessage::getRoomId() const {
    return roomid;
}

std::string ChatMessage::getUserId() const {
    return userid;
}

std::string ChatMessage::getSendTime() const {
    return sendtime;
}

std::string ChatMessage::getMessage() const {
    return message;
}

std::string ChatMessage::getUsername() const {
    return username;
}

