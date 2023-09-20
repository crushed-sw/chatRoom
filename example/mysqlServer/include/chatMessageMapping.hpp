#ifndef __CHAT_MESSAGE_MAPPING_HPP
#define __CHAT_MESSAGE_MAPPING_HPP

#include "../../../include/mysql/MySql.hpp"
#include "../../../include/mysql/MySqlConn.hpp"

#include "../entity/include/chatMessage.hpp"

class ChatMessageMapping {
public:
    void insert(const ChatMessage& message);
};

#endif //__CHAT_MESSAGE_MAPPING_HPP
