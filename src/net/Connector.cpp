#include "../../include/net/Connector.hpp"
#include "../../include/net/Channel.hpp"
#include "../../include/net/EventLoop.hpp"

using namespace crushed::net;

static EventLoop* checkNotNullptr(EventLoop* loop) {
    if(loop == nullptr) {
        LogFatal << "tcpConnection loop is nullptr" << LogEnd;
    }
    return loop;
}


Connector::Connector(EventLoop* loop, const InetAddress& address)
        : loop_(checkNotNullptr(loop))
        , address_(address)
        , connect_(false)
        , state_(Disconnected)
        , relayTime_(InitRetryDelay) {
    LogInfo << "client actor[" << this << "]" << LogEnd;
}

Connector::~Connector() {
    LogInfo << "client dctor[" << this << "]" << LogEnd;
}

void Connector::setNewConnectionCallback(const NewConnectionCallback& cb) {
    newConnectionCallback_ = cb;
}

void Connector::start() {
    connect_ = true;
    loop_->runInLoop(std::bind(&Connector::startInLoop, this));
}

void Connector::restart() {
    state_ = Disconnected;
    relayTime_ = InitRetryDelay;
    connect_ = true;
    startInLoop();
}

void Connector::stop() {
    connect_ = false;
    loop_->queueInLoop(std::bind(&Connector::stopInLoop, this));
}

const InetAddress& Connector::getAddress() const {
    return address_;
}

int Connector::removeAndResetChannel() {
    channel_->disableAll();
    channel_->remove();
    int sockfd = channel_->fd();
    loop_->queueInLoop(std::bind(&Connector::resetChannel, this));
    return sockfd;
}

void Connector::resetChannel() {
    channel_.reset();
}

void Connector::connect() {
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if(sockfd < 0) {
        LogFatal << "Connector::connect() erorr" << LogEnd;
    }

    int ret = ::connect(sockfd, (sockaddr*)address_.getSockAddr(), sizeof(sockaddr_in));
    int saveError = (ret == 0) ? 0 : errno;

    if(saveError == 0 || saveError == EINTR || saveError == EINPROGRESS || saveError == EISCONN)
        connecting(sockfd);
    else if(saveError == EAGAIN || saveError == EADDRINUSE || saveError == ECONNREFUSED || saveError == ENETUNREACH)
        retry(sockfd);
    else
        LogError << "connection error in Connector::connect" << LogEnd;

}


void Connector::connecting(int sockfd) {
    state_ = Connecting;
    channel_.reset(new Channel(loop_, sockfd));
    channel_->setWriteCallBack(std::bind(&Connector::handleWrite, this));
    channel_->setErrorCallBack(std::bind(&Connector::handleError, this));
    channel_->enableWrite();
}

void Connector::startInLoop() {
    if(connect_) {
        connect();
    } else {
        LogError << "do not connect" << LogEnd;
    }
}

void Connector::stopInLoop() {
    if(state_ == Connecting) {
        state_ = Disconnected;

        int sockfd = removeAndResetChannel();

        retry(sockfd);
    }
}

void Connector::retry(int sockfd) {
    ::close(sockfd);
    state_ = Disconnected;
    if(connect_) {
        loop_->runInLoop(std::bind(&Connector::startInLoop, shared_from_this()));
    }
}

void Connector::handleWrite() {
    if(state_ == Connecting) {
        int sockfd = removeAndResetChannel();

        int optval = 0;
        socklen_t optlen = sizeof(optval);
        int saveError = ::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen);
        if(saveError < 0)
            saveError = errno;

        if(saveError) {
            retry(sockfd);
        } else {
            state_ = Connected;
            if(connect_) {
                newConnectionCallback_(sockfd);
            } else {
                ::close(sockfd);
            }
        }
    }
}

void Connector::handleError() {
    if(state_ == Connecting) {
        int sockfd = removeAndResetChannel();

        int optval = 0;
        socklen_t optlen = sizeof(optval);
        int saveError = ::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen);
        if(saveError < 0)
            saveError = errno;

        retry(sockfd);
    }
}
