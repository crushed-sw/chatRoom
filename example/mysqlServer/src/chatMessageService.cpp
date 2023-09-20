#include "../include/chatMessageService.hpp"

void ChatMessageService::insertChatMessage(::google::protobuf::RpcController* controller,
                                           const ::crushed::ChatMessageInsertRequest* request,
                                           ::crushed::ChatMessageInsertResponse* response,
                                           ::google::protobuf::Closure* done) {
    try {
        crushed::ChatMessage rpcChatMessage = request->chatmessage();
        ChatMessage chatMessage;
        RpcEntity::rpcToEntity(&rpcChatMessage, chatMessage);

        chatMessageMapping_.insert(chatMessage);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "mysql异常", result);
    }

    done->Run();
}
