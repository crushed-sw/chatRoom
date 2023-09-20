#include "../include/chatMessageService.hpp"

ChatMessageService::ChatMessageService()
        : ip_(crushed::net::ServerApplication::getConfig().getValue("mysql_server_ip"))
        , port_(std::atoi(crushed::net::ServerApplication::getConfig().getValue("mysql_server_port").c_str())) {}

ChatMessageService::~ChatMessageService() {}

void ChatMessageService::insert(const ChatMessage& message) {
    crushed::ChatMessageMappinngService_Stub stub(new crushed::rpc::RpcChannel(ip_, port_));
    crushed::rpc::RpcController controller;

    crushed::ChatMessageInsertRequest request;
    crushed::ChatMessageInsertResponse response;

    crushed::ChatMessage* rpcMessage = request.mutable_chatmessage();

    RpcEntity::entityToRpc(message, rpcMessage);

    stub.insertChatMessage(&controller, &request, &response, nullptr);

    if(!controller.Failed()) {
        if(response.result().code() != 200) {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }
}
