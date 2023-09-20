#include "../../include/net/Acceptor.hpp"
#include "../../include/net/EventLoop.hpp"

using namespace crushed::net;

Acceptor::Acceptor(EventLoop* loop, const InetAddress& address, bool reuseport)
        : loop_(loop)
        , acceptSocket_(Acceptor::createNonBloking())
        , acceptChannel_(loop, acceptSocket_.fd())
        , listening_(false) {
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(true);
    acceptSocket_.bindAddress(address);
    acceptChannel_.setReadCallBack(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor() {
    acceptChannel_.disableAll();
    acceptChannel_.remove();
}

void Acceptor::setNewConnectionCallBack(const newConnectionCallBack& cb) {
    newConnectionCallBack_ = cb;
}

bool Acceptor::listening() const {
    return listening_;
}

void Acceptor::listen() {
    listening_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableRead();
}

void Acceptor::handleRead() {
    InetAddress peerAddress(0);
    int connfd = acceptSocket_.accept(&peerAddress);
    if(connfd >= 0) {
        if(newConnectionCallBack_) {
            newConnectionCallBack_(connfd, peerAddress);
        } else {
            ::close(connfd);
        }
    } else {
        LogError << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << " accept socket error: " << errno << LogEnd;
    }
}

int Acceptor::createNonBloking() {
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if(sockfd < 0) {
        LogFatal << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << " create socket error: " << errno << LogEnd;
    }
    return sockfd;
}
