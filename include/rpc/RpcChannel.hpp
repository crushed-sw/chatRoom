#ifndef __RPC_CHANNEL_HPP
#define __RPC_CHANNEL_HPP

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include <string>

#include "rpcHeader.pb.h"
#include "../net/ServerApplication.hpp"
#include "../net/Log.hpp"
#include "../net/TcpClient.hpp"

namespace crushed {
namespace rpc {

class RpcChannel : public google::protobuf::RpcChannel {
public:
    RpcChannel();
    RpcChannel(const std::string& ip, int port);

    void CallMethod(const google::protobuf::MethodDescriptor* method, 
                    google::protobuf::RpcController* controller, 
                    const google::protobuf::Message* request, 
                    google::protobuf::Message* response, 
                    google::protobuf::Closure* done);

    void setIp(const std::string& ip);
    void setPort(int port);

    std::string getIP();
    int getPort();

private:
    void onConntion(const net::TcpConnectionPtr& conn, const std::string& str);
    void onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buf, 
                   net::Timer time, google::protobuf::Message*& response, 
                   net::EventLoop* loop, google::protobuf::RpcController* controller);

    std::string ip_;
    int port_;
};

} // namespace rpc
} // namespace crushed

#endif //__RPC_CHANNEL_HPP
