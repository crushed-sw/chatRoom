#ifndef __MY_SQL_CONN_HPP
#define __MY_SQL_CONN_HPP

#include "MySqlPool.hpp"

namespace crushed {
namespace mysql {

class MySqlConn {
public:
    MySqlConn(MySql*& mysql, MySqlPool& mysqlPool);
    MySqlConn(MySql*& mysql, MySqlPool& mysqlPool, const std::string& table);
    ~MySqlConn();

private:
    MySql* mysql_;
    MySqlPool* pool_;
};

} // namespace mysql
} // namespace crushed

#endif //__MY_SQL_CONN_HPP
