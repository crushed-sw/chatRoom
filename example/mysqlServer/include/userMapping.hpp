#ifndef __USER_MAPPING_HPP
#define __USER_MAPPING_HPP

#include "../../../include/mysql/MySqlPool.hpp"
#include "../../../include/mysql/MySqlConn.hpp"

#include "../entity/include/user.hpp"

class UserMapping {
public:
    User query(int userid);
    void insert(const User& user);
};

#endif // __USER_MAPPING_HPP
