#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP

#include "TcpConnection.hpp"
#include "EventLoop.hpp"
#include "EventLoopThreadPool.hpp"
#include "Acceptor.hpp"
#include "InetAddress.hpp"
#include "NonCopyable.hpp"
#include "Callbacks.hpp"
#include "Log.hpp"

#include <functional>
#include <string>
#include <atomic>
#include <unordered_map>

namespace crushed {
namespace net {

class TcpServer : public NonCopyable {
public:
    using ThreadInitCallBack = std::function<void(EventLoop*)>;
    enum Option { NoReusePort, ReusePort };

    TcpServer(EventLoop* loop, const InetAddress& address, const std::string& name, Option option = ReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallBack& cb);
    void setThreadNum(int numThreads);

    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setCloseCallback(const CloseCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);

    void start();

private:
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

    void newConnection(int sockfd, const InetAddress& address);
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

    EventLoop* loop_;
    const std::string ipPort_;
    const std::string name_;

    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    CloseCallback closeCallback_;
    WriteCompleteCallback writeCompleteCallback_;

    ThreadInitCallBack threadInitCallBack_;
    std::atomic_int started_;

    int nextConnId_;
    ConnectionMap Connections_;
};

} // namespace net
} // namespace crushed

#endif //__TCP_SERVER_HPP
