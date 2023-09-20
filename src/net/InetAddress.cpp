#include "../../include/net/InetAddress.hpp"

using namespace crushed::net;

InetAddress::InetAddress(uint16_t port, const std::string& ip) {
    bzero(&address_, sizeof(address_));
    address_.sin_port = htons(port);
    address_.sin_addr.s_addr = inet_addr(ip.c_str());
    address_.sin_family = AF_INET;
}

InetAddress::InetAddress(const sockaddr_in& address) : address_(address) {}

std::string InetAddress::getIp() const {
    char buf[INET_ADDRSTRLEN] = {};
    inet_ntop(AF_INET, &address_.sin_addr, buf, INET_ADDRSTRLEN);
    return buf;
}

uint16_t InetAddress::getPort() const {
    return ntohs(address_.sin_port);
}

std::string InetAddress::getIpPort() const {
    char buf[64] = {};
    sprintf(buf, "%s:%u", getIp().c_str(), getPort());
    return buf;
}

const sockaddr_in* InetAddress::getSockAddr() const {
    return &address_;
}

void InetAddress::setAocksddr(const sockaddr_in& addr) {
    address_ = addr;
}

