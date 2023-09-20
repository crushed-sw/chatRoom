#include "../include/userService.hpp"

void UserService::queryUser(::google::protobuf::RpcController* controller,
                            const ::crushed::UserQueryRequest* request,
                            ::crushed::UserQueryResponse* response,
                            ::google::protobuf::Closure* done) {
    try {
        int userid = request->userid();

        User user = userMapping_.query(userid);

        crushed::User* rpcUser = response->mutable_user();
        RpcEntity::entityToRpc(user, rpcUser);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        std::cout << "exception" << std::endl;
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "mysql异常", result);
    }

    done->Run();
}

void UserService::insertUser(::google::protobuf::RpcController* controller,
                             const ::crushed::UserInsertRequest* request,
                             ::crushed::UserInsertResponse* response,
                             ::google::protobuf::Closure* done) {
    try {
        crushed::User rpcUser = request->user();
        User user;
        RpcEntity::rpcToEntity(&rpcUser, user);

        userMapping_.insert(user);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "mysql异常", result);
    }

    done->Run();
}


