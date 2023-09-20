#ifndef __MY_SQL_POOL_HPP
#define __MY_SQL_POOL_HPP

#include <string>
#include <cstdlib>

#include "../net/Log.hpp"
#include "../net/ServerApplication.hpp"
#include "../net/ServerConfig.hpp"
#include "../net/SyncQueue.hpp"
#include "MySql.hpp"

namespace crushed {
namespace mysql {

class MySqlPool {
public:
    ~MySqlPool();

    static MySqlPool& getInstance();

    MySql* getConnection();
    MySql* getConnection(const std::string& table);
    void releaseConnection(MySql* mysql);

private:
    MySqlPool();

    MySqlPool(const MySqlPool&) = delete;
    MySqlPool(MySqlPool&&) = delete;
    MySqlPool operator=(const MySqlPool&) = delete;
    MySqlPool  operator=(MySqlPool&&) = delete;

    std::string url_;
    std::string user_;
    std::string password_;
    int poolSize_;
    net::SyncQueue<MySql*> pool_;
};

} // namespace mysql
} // namespace crushed

#endif //__MY_SQL_POOL_HPP
