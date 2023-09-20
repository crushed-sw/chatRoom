#ifndef __INET_ADDRESS_HPP
#define __INET_ADDRESS_HPP

#include <string>
#include <cstring>

#include <arpa/inet.h>
#include <netinet/in.h>

namespace crushed {
namespace net {

class InetAddress {
public:
    explicit InetAddress(uint16_t port, const std::string& ip = "0.0.0.0");
    explicit InetAddress(const sockaddr_in& address);

    std::string getIp() const;
    uint16_t getPort() const;
    std::string getIpPort() const;

    const sockaddr_in* getSockAddr() const;
    void setAocksddr(const sockaddr_in& addr);

private:
    sockaddr_in address_;
};

} // namespace net
} // namespace crushed

#endif //__INET_ADDRESS_HPP
