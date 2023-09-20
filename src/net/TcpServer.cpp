#include "../../include/net/TcpServer.hpp"
#include "../../include/net/TcpServer.hpp"

using namespace crushed::net;
using namespace std::placeholders;

static EventLoop* checkNotNullptr(EventLoop* loop) {
    if(loop == nullptr) {
        LogFatal << "main loop is nullptr" << LogEnd;
    }
    return loop;
}

TcpServer::TcpServer(EventLoop* loop, const InetAddress& address, const std::string& name, Option option)
        : loop_(checkNotNullptr(loop))
        , ipPort_(address.getIpPort())
        , name_(name)
        , acceptor_(new Acceptor(loop, address, option == ReusePort))
        , threadPool_(new EventLoopThreadPool(loop, name))
        , started_(0)
        , nextConnId_(1) {
    acceptor_->setNewConnectionCallBack(std::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer() {
    for(auto& item : Connections_) {
        TcpConnectionPtr conn(item.second);
        item.second.reset();

        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestory, conn));
    }
}

void TcpServer::setThreadInitCallback(const ThreadInitCallBack& cb) {
    threadInitCallBack_ = cb;
}

void TcpServer::setThreadNum(int numThreads) {
    threadPool_->setThreadNum(numThreads);
}

void TcpServer::setConnectionCallback(const ConnectionCallback& cb) {
    connectionCallback_ = cb;
}

void TcpServer::setMessageCallback(const MessageCallback& cb) {
    messageCallback_ = cb;
}

void TcpServer::setCloseCallback(const CloseCallback& cb) {
    closeCallback_ = cb;
}

void TcpServer::setWriteCompleteCallback(const WriteCompleteCallback& cb) {
    writeCompleteCallback_ = cb;
}

void TcpServer::start() {
    if(started_ == 0) {
        started_++;
        threadPool_->start(threadInitCallBack_);
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

void TcpServer::newConnection(int sockfd, const InetAddress& address) {
    EventLoop* loop = threadPool_->getNextLoop();
    char buf[64] = {};
    snprintf(buf, sizeof(buf), "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    LogInfo << "TcpServer::newConnection " << name_ << " - new connection " << connName << " from " << address.getIpPort() << LogEnd;

    sockaddr_in local = {};
    socklen_t addrlen = sizeof(local);
    int ret = getsockname(sockfd, (sockaddr*)&local, &addrlen);
    if(ret < 0) {
        LogError << "getsockname error" << LogEnd;
    }
    InetAddress localAddress(local);
    
    TcpConnectionPtr conn(new TcpConnection(loop, connName, sockfd, localAddress, address));

    Connections_[connName] = conn;
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setCloseCallback(closeCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);

    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, _1));
    loop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn) {
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
    closeCallback_(conn);
    LogInfo << "TcpServer::removeConnectionInLoop " << name_ << " - connection " << conn->name() << LogEnd;
    Connections_.erase(conn->name());
    EventLoop* loop = conn->getLoop();
    loop->queueInLoop(std::bind(&TcpConnection::connectDestory, conn));
}

