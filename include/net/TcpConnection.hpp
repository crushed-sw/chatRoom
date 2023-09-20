#ifndef __TCP_CONNEXCTION_HPP
#define __TCP_CONNEXCTION_HPP

#include "Buffer.hpp"
#include "NonCopyable.hpp"
#include "InetAddress.hpp"
#include "Callbacks.hpp"
#include "Timer.hpp"

#include <memory>
#include <string>
#include <atomic>

namespace crushed {
namespace net {

class Channel;
class EventLoop;
class Socket;

class TcpConnection : public NonCopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& localAddress, const InetAddress& peerAddress);
    ~TcpConnection();

    EventLoop* getLoop() const;
    const std::string& name() const;
    const InetAddress& localAddress() const;
    const InetAddress& peerAddress() const;

    bool connected() const;
    void send(const std::string& str);

    void shutdown();

    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);
    void setCloseCallback(const CloseCallback& cb);

    void connectEstablished();
    void connectDestory();

private:
    enum State {Disconnected, Connecting, Connected, Disconnecting};

    void handleRead(Timer timer);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void* message, int len);
    void shutdownInLoop();

    EventLoop* loop_;
    const std::string name_;
    std::atomic_int state_;
    bool reading_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    const InetAddress localAddress_;
    const InetAddress peerAddress_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;

    Buffer inputBuffer_;
    Buffer outputBuffer_;
};

} // namespace net
} // namespace crushed

#endif //__TCP_CONNEXCTION_HPP
