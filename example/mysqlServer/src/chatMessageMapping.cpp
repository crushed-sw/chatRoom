#include "../include/chatMessageMapping.hpp"

void ChatMessageMapping::insert(const ChatMessage& message) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "chat");

    mysql->insert(message, "chatid");
}
