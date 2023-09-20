#include "../../include/net/Socket.hpp"

using namespace crushed::net;

Socket::Socket(int sockfd) : sockfd_(sockfd) {}

Socket::~Socket() {
    close(sockfd_);
}

int Socket::fd() const {
    return sockfd_;
}

void Socket::bindAddress(const InetAddress& localAddress) {
    int ret = ::bind(sockfd_, (sockaddr*)localAddress.getSockAddr(), sizeof(sockaddr_in));
    if(ret != 0) {
        LogFatal << "bind sockfd: " << sockfd_ << " error" << LogEnd;
    }
}

void Socket::listen() {
    int ret = ::listen(sockfd_, 1024);
    if(ret != 0) {
        LogFatal << "listen sockfd: " << sockfd_ << " error" << LogEnd;
    }
}

int Socket::accept(InetAddress* peerAddress) {
    sockaddr_in client = {};
    socklen_t clientLen = sizeof(client);
    int connfd = ::accept4(sockfd_, (sockaddr*)&client, &clientLen, SOCK_NONBLOCK);
    if(connfd >= 0) {
        peerAddress->setAocksddr(client);
    }

    return connfd;
}

void Socket::shutdownWrite() {
    int ret = ::shutdown(sockfd_, SHUT_WR);
    if(ret < 0) {
        LogError << "sockfd: " << sockfd_ << "shutdown error" << LogEnd;
    }
}

void Socket::setTcpNoDelay(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

void Socket::setReuseAddr(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void Socket::setReusePort(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}

