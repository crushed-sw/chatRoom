#include "../../include/mysql/MySqlConn.hpp"

using namespace crushed::mysql;

MySqlConn::MySqlConn(MySql*& mysql, MySqlPool& pool, const std::string& table) : pool_(&pool) {
    mysql_ = pool.getConnection(table);
    mysql = mysql_;
}

MySqlConn::MySqlConn(MySql*& mysql, MySqlPool& pool) : pool_(&pool) {
    mysql_ = pool.getConnection();
    mysql = mysql_;
}

MySqlConn::~MySqlConn() {
    pool_->releaseConnection(mysql_);
}
