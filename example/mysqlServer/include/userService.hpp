#ifndef __USER_SERVICE_HPP
#define __USER_SERVICE_HPP

#include "../entity/include/user.hpp"
#include "../entity/include/rpcEntiry.hpp"

#include "userMapping.hpp"
#include "mysql.pb.h"

class UserService : public crushed::UserMappingService {
public:
    void queryUser(::google::protobuf::RpcController* controller,
                   const ::crushed::UserQueryRequest* request,
                   ::crushed::UserQueryResponse* response,
                   ::google::protobuf::Closure* done) override;

    void insertUser(::google::protobuf::RpcController* controller,
                    const ::crushed::UserInsertRequest* request,
                    ::crushed::UserInsertResponse* response,
                    ::google::protobuf::Closure* done) override;

private:
    UserMapping userMapping_;
};

#endif //__USER_SERVICE_HPP
