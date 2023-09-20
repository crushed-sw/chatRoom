#ifndef __CHAT_MESSAGE_SERVICE_HPP
#define __CHAT_MESSAGE_SERVICE_HPP

#include "../entity/include/chatMessage.hpp"

#include "chatMessageMapping.hpp"
#include "../entity/include/rpcEntiry.hpp"
#include "mysql.pb.h"

class ChatMessageService : public crushed::ChatMessageMappinngService {
public:
    void insertChatMessage(::google::protobuf::RpcController* controller,
                           const ::crushed::ChatMessageInsertRequest* request,
                           ::crushed::ChatMessageInsertResponse* response,
                           ::google::protobuf::Closure* done) override;

private:
    ChatMessageMapping chatMessageMapping_;
};

#endif //__CHAT_MESSAGE_SERVICE_HPP
