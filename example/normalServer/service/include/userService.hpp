#ifndef __USER_SERVICE_HPP
#define __USER_SERVICE_HPP

#include "../../../../include/net/Log.hpp"
#include "../../../../include/rpc/RpcChannel.hpp"
#include "../../../../include/rpc/RpcController.hpp"
#include "../../../../include/net/ServerApplication.hpp"

#include "../../entity/include/mysql.pb.h"
#include "../../entity/include/rpcEntiry.hpp"

#include <exception>

class UserService {
public:
    UserService();
    ~UserService();

    User query(int userid);
    void insert(const User& user);

private:
    std::string ip_;
    int port_;
};

#endif //__USER_SERVICE_HPP
