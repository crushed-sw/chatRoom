#ifndef __RPC__PROVIDER_HPP
#define __RPC__PROVIDER_HPP

#include "../net/ServerApplication.hpp"
#include "../net/Log.hpp"
#include "../net/TcpServer.hpp"
#include "rpcHeader.pb.h"

#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"

#include <thread>
#include <unordered_map>

namespace crushed {
namespace rpc {

class RpcProvider {
public:
    void notifyService(google::protobuf::Service* service);
    void run();

private:
    void onConntion(const net::TcpConnectionPtr& conn);
    void onClose(const net::TcpConnectionPtr& conn);
    void onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buf, net::Timer time);
    void sendRpcResponse(const net::TcpConnectionPtr& conn, google::protobuf::Message* message);

    net::EventLoop eventLoop_;

    struct ServerInfo {
        google::protobuf::Service* server_;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> methodMap_;
    };
    std::unordered_map<std::string, ServerInfo> serverMap_;
};

} // namespace rpc
} // namespace crushed

#endif //__RPC__PROVIDER_HPP
