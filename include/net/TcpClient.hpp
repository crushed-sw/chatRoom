#ifndef __TCP_CLIENT_HPP
#define __TCP_CLIENT_HPP

#include "TcpConnection.hpp"
#include "NonCopyable.hpp"
#include "Callbacks.hpp"
#include "EventLoop.hpp"
#include "InetAddress.hpp"
#include "Log.hpp"

#include <atomic>
#include <functional>

namespace crushed {
namespace net {

class TcpClient : public NonCopyable {
public:
    TcpClient(EventLoop* loop, const InetAddress& address, const std::string& name);
    ~TcpClient();

    void connect();
    void disconnect();
    void stop();

    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);

private:
    void newConnection(int sockfd);
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionLoop(EventLoop* loop, const TcpConnectionPtr& conn);

    EventLoop* loop_;
    ConnectorPtr conn_;

    std::string name_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;

    std::atomic_bool retry_;
    std::atomic_bool connect_;

    int nextId_;
    std::mutex mutex_;

    TcpConnectionPtr conntion_;
};

} // namespace net
} // namespace crushed

#endif // __TCP_CLIENT_HPP
