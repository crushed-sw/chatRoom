#include "../include/userService.hpp"

UserService::UserService()
        : ip_(crushed::net::ServerApplication::getConfig().getValue("mysql_server_ip"))
        , port_(std::atoi(crushed::net::ServerApplication::getConfig().getValue("mysql_server_port").c_str())) {}

UserService::~UserService() {}

User UserService::query(int userid) {
    crushed::UserMappingService_Stub stub(new crushed::rpc::RpcChannel(ip_, port_));
    crushed::rpc::RpcController controller;

    crushed::UserQueryRequest request;
    crushed::UserQueryResponse response;

    request.set_userid(userid);

    stub.queryUser(&controller, &request, &response, nullptr);

    User user;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            crushed::User rpcUser = response.user();
            RpcEntity::rpcToEntity(&rpcUser, user);
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return user;
}

void UserService::insert(const User& user) {
    crushed::UserMappingService_Stub stub(new crushed::rpc::RpcChannel(ip_, port_));
    crushed::rpc::RpcController controller;

    crushed::UserInsertRequest request;
    crushed::UserInsertResponse response;

    crushed::User* rpcUser = request.mutable_user();

    RpcEntity::entityToRpc(user, rpcUser);

    stub.insertUser(&controller, &request, &response, nullptr);

    if(!controller.Failed()) {
        if(response.result().code() != 200) {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }
}
