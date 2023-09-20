#include "../include/userMapping.hpp"

User UserMapping::query(int userid) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "user");

    return mysql->queryById<User>("userid", userid);
}

void UserMapping::insert(const User& user) {
    crushed::mysql::MySql* mysql = nullptr;
    crushed::mysql::MySqlPool& pool = crushed::mysql::MySqlPool::getInstance();
    crushed::mysql::MySqlConn conn(mysql, pool, "user");

    mysql->insert(user);
}


