#include "../../include/net/TcpConnection.hpp"
#include "../../include/net/Socket.hpp"
#include "../../include/net/EventLoop.hpp"
#include "../../include/net/Channel.hpp"
#include "../../include/net/Log.hpp"

using namespace crushed::net;
using namespace std::placeholders;

static EventLoop* checkNotNullptr(EventLoop* loop) {
    if(loop == nullptr) {
        LogFatal << "tcpConnection loop is nullptr" << LogEnd;
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop* loop, const std::string& name, int sockfd, const InetAddress& localAddress, const InetAddress& peerAddress)
        : loop_(checkNotNullptr(loop))
        , name_(name)
        , state_(Connecting)
        , reading_(true)
        , socket_(new Socket(sockfd))
        , channel_(new Channel(loop, sockfd))
        , localAddress_(localAddress)
        , peerAddress_(peerAddress) {
    channel_->setReadCallBack(std::bind(&TcpConnection::handleRead, this, _1));
    channel_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallBack(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallBack(std::bind(&TcpConnection::handleError, this));

    LogInfo << "TcpConnection::actor[" << name << "] at fd: " << sockfd << LogEnd;
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection() {
    LogInfo << "TcpConnection::dctor[" << name_ << "] at fd: " << channel_->fd() << LogEnd;
}

EventLoop* TcpConnection::getLoop() const {
    return loop_;
}

const std::string& TcpConnection::name() const {
    return name_;
}

const InetAddress& TcpConnection::localAddress() const {
    return localAddress_;
}

const InetAddress& TcpConnection::peerAddress() const {
    return peerAddress_;
}

bool TcpConnection::connected() const {
    return state_ == Connected;
}

void TcpConnection::send(const std::string& str) {
    if(state_ == Connected) {
        if(loop_->isInLoopThread()) {
            sendInLoop(str.c_str(), str.size());
        } else {
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, str.c_str(), str.size()));
        }
    }
}

void TcpConnection::shutdown() {
    if(state_ == Connected) {
        state_ = Disconnecting;
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::setConnectionCallback(const ConnectionCallback& cb) {
    connectionCallback_ = cb;
}

void TcpConnection::setMessageCallback(const MessageCallback& cb) {
    messageCallback_ = cb;
}

void TcpConnection::setWriteCompleteCallback(const WriteCompleteCallback& cb) {
    writeCompleteCallback_ = cb;
}

void TcpConnection::setCloseCallback(const CloseCallback& cb) {
    closeCallback_ = cb;
}

void TcpConnection::connectEstablished() {
    state_ = Connected;
    channel_->tie(shared_from_this());
    channel_->enableRead();
    connectionCallback_(shared_from_this());
}

void TcpConnection::connectDestory() {
    if(state_ == Connected) {
        state_ = Disconnected;
        channel_->disableAll();
        connectionCallback_(shared_from_this());
    }
    channel_->remove();
}

void TcpConnection::handleRead(Timer timer) {
    int saveErrno = 0;
    std::size_t len = inputBuffer_.readFd(channel_->fd(), saveErrno);
    if(len > 0) {
        messageCallback_(shared_from_this(), &inputBuffer_, timer);
    } else if(len == 0) {
        handleClose();
    } else {
        LogError << "TcpConnection::handleRead error: " << saveErrno << LogEnd;
        handleError();
    }
}

void TcpConnection::handleWrite() {
    if(channel_->isWriteEvent()) {
        int saveErrno = 0;
        std::size_t len = outputBuffer_.writeFd(channel_->fd(), saveErrno);
        if(len > 0) {
            outputBuffer_.retrieve(len);
            if(outputBuffer_.readableBytes() == 0) {
                channel_->disableWrite();
                if(writeCompleteCallback_) {
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if(state_ == Disconnecting) {
                    shutdownInLoop();
                }
            }
        } else {
            LogError << "TcpConnection::handleWrite error: " << saveErrno << LogEnd;
        }
    } else {
        LogError << "TcpConnection is down, no more write " << LogEnd;
    }
}

void TcpConnection::handleClose() {
    state_ = Disconnected;
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());

    if(connectionCallback_)
        connectionCallback_(connPtr);
    if(closeCallback_)
        closeCallback_(connPtr);
}

void TcpConnection::handleError() {
    int err;
    int optval = 0;
    socklen_t optlen = sizeof(optval);
    int ret = getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen);
    if(ret < 0) {
        err = errno;
    } else {
        err = optval;
    }

    LogError << "TcpConnection::handleError" << LogEnd;
}

void TcpConnection::sendInLoop(const void* message, int len) {
    std::size_t nwrite = 0;
    std::size_t remaining = len;
    bool faultError = false;

    if(state_ == Disconnected) {
        LogError << "idsconnected, give up writing" << LogEnd;
        return;
    }

    if(!channel_->isWriteEvent() && outputBuffer_.readableBytes() == 0) {
        nwrite = write(channel_->fd(), message, len);
        if(nwrite >= 0) {
            remaining = len - nwrite;
            if(remaining == 0 && writeCompleteCallback_) {
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        } else {
            nwrite = 0;
            if(errno != EWOULDBLOCK) {
                LogError << "TcpConnection::sendInLoop error: " << errno << LogEnd;
                if(errno == EPIPE || errno == ECONNRESET) {
                    faultError = true;
                }
            }
        }
    }

    if(!faultError && remaining > 0) {
        outputBuffer_.append((char*)message + nwrite, remaining);
        if(!channel_->isWriteEvent()) {
            channel_->enableWrite();
        }
    }
}

void TcpConnection::shutdownInLoop() {
    if(!channel_->isWriteEvent()) {
        socket_->shutdownWrite();
    }
}
