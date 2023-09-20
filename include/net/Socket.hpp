#ifndef __SOCKET_HPP
#define __SOCKET_HPP

#include "NonCopyable.hpp"
#include "Log.hpp"
#include "InetAddress.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>

namespace crushed {
namespace net {

class Socket : public NonCopyable {
public:
    explicit Socket(int sockfd);
    ~Socket();

    int fd() const;
    void bindAddress(const InetAddress& localAddress);
    void listen();
    int accept(InetAddress* peerAddress);

    void shutdownWrite();

    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);

private:
    const int sockfd_;
};

} // namespace net
} // namespace crushed

#endif //__SOCKET_HPP

