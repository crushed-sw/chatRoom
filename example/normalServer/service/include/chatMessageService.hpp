#ifndef __CHAT_MESSAGE_SERVICE_HPP
#define __CHAT_MESSAGE_SERVICE_HPP

#include "../../../../include/net/Log.hpp"
#include "../../../../include/rpc/RpcChannel.hpp"
#include "../../../../include/rpc/RpcController.hpp"
#include "../../../../include/net/ServerApplication.hpp"

#include "../../entity/include/mysql.pb.h"
#include "../../entity/include/rpcEntiry.hpp"
#include <exception>

class ChatMessageService {
public:
    ChatMessageService();
    ~ChatMessageService();

    void insert(const ChatMessage& message);

private:
    std::string ip_;
    int port_;
};

#endif //__CHAT_MESSAGE_SERVICE_HPP
