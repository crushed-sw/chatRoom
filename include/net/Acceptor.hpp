#ifndef __ACCEPTOR_HPP
#define __ACCEPTOR_HPP

#include "NonCopyable.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "Channel.hpp"
#include "Log.hpp"

#include <functional>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace crushed {
namespace net {

class EventLoop;

class Acceptor : public NonCopyable {
public:
    using newConnectionCallBack = std::function<void(int, const InetAddress&)>;

    Acceptor(EventLoop* loop, const InetAddress& address, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallBack(const newConnectionCallBack& cb);

    bool listening() const;
    void listen();

private:
    void handleRead();
    static int createNonBloking();

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;

    newConnectionCallBack newConnectionCallBack_;
    bool listening_;
};

} // namespace net
} // namespace crushed

#endif //__ACCEPTOR_HPP
