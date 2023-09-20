#ifndef __CHAT_MESSAGE_HPP
#define __CHAT_MESSAGE_HPP

#include "../../../../thirdparty/json.hpp"

class ChatMessage {
public:
    ChatMessage(const std::string& chatid = "", const std::string& roomid = "",
                const std::string& userid = "", const std::string& sendtime = "",
                const std::string& message = "");

    ChatMessage(const std::vector<std::string>& vec);
    std::map<std::string, std::string> get() const;

    void setChatId(const std::string& chatid);
    void setRoomId(const std::string& roomid);
    void setUserId(const std::string& userid);
    void setSendTime(const std::string& sendtime);
    void setMessage(const std::string& message);
    void setUsername(const std::string& username);

    std::string getChatId() const;
    std::string getRoomId() const;
    std::string getUserId() const;
    std::string getSendTime() const;
    std::string getMessage() const;
    std::string getUsername() const;

private:
    std::string chatid;
    std::string roomid;
    std::string userid;
    std::string sendtime;
    std::string message;
    std::string username;
};

#endif //__CHAT_MESSAGE_HPP
