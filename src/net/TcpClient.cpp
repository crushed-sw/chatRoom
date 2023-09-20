#include "../../include/net/TcpClient.hpp"
#include "../../include/net/Connector.hpp"
#include "../../include/net/TcpConnection.hpp"

using namespace crushed::net;
using namespace std::placeholders;


static EventLoop* checkNotNullptr(EventLoop* loop) {
    if(loop == nullptr) {
        LogFatal << "main loop is nullptr" << LogEnd;
    }
    return loop;
}

TcpClient::TcpClient(EventLoop* loop, const InetAddress& address, const std::string& name)
        : loop_(checkNotNullptr(loop))
        , conn_(new Connector(loop, address))
        , name_(name)
        , retry_(false)
        , connect_(true)
        , nextId_(1) {
    conn_->setNewConnectionCallback(std::bind(&TcpClient::newConnection, this, _1));
    LogInfo << "TcpClient::TcpClient[" << name_ << "] - connector " << conn_.get();
}

TcpClient::~TcpClient() {
    LogInfo << "TcpClient::~TcpClient[" << name_ << "] - connector " << conn_.get();
    TcpConnectionPtr conn;
    bool unique = false;
    {
        std::unique_lock<std::mutex> locker(mutex_);
        unique = conntion_.unique();
        conn = conntion_;
    }


    if(conn) {
        CloseCallback cb = std::bind(&TcpClient::removeConnectionLoop, this, loop_, _1);
        loop_->runInLoop(std::bind(&TcpConnection::setCloseCallback, conn, cb));
        if(unique) {
            conn->shutdown();
        }
    } else {
        conn_->stop();
    }
}

void TcpClient::connect() {
    connect_ = true;
    conn_->start();
}

void TcpClient::disconnect() {
    connect_ = false;
    {
        std::unique_lock<std::mutex> locker(mutex_);
        if(conntion_) {
            conntion_->shutdown();
        }
    }
}

void TcpClient::stop() {
    connect_ = false;
    conn_->stop();
}

void TcpClient::setConnectionCallback(const ConnectionCallback& cb) {
    connectionCallback_ = cb;
}

void TcpClient::setMessageCallback(const MessageCallback& cb) {
    messageCallback_ = cb;
}

void TcpClient::setWriteCompleteCallback(const WriteCompleteCallback& cb) {
    writeCompleteCallback_ = cb;
}

void TcpClient::newConnection(int sockfd) {
    sockaddr_in address = {};
    socklen_t addressLen = sizeof(address);
    int ret = getpeername(sockfd, (sockaddr*)&address, &addressLen);
    if(ret < 0) {
        LogError << "getpeername error" << LogEnd;
    }

    InetAddress peerAddress(address);
    char buf[32] = {};
    snprintf(buf, sizeof(buf), ":%s#%d", peerAddress.getIpPort().c_str(), nextId_);
    ++nextId_;
    std::string connName = name_ + buf;

    sockaddr_in local = {};
    socklen_t localLen = sizeof(local);
    ret = getsockname(sockfd, (sockaddr*)&local, &localLen);
    if(ret < 0) {
        LogError << "getpeername error" << LogEnd;
    }
    InetAddress localAddress(local);

    TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockfd, localAddress, peerAddress));
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpClient::removeConnection, this, _1));

    {
        std::unique_lock<std::mutex> locker(mutex_);
        conntion_ = conn;
    }
    conn->connectEstablished();
}

void TcpClient::removeConnectionLoop(EventLoop* loop, const TcpConnectionPtr& conn) {
    loop->queueInLoop(std::bind(&TcpConnection::connectDestory, conn));
}

void TcpClient::removeConnection(const TcpConnectionPtr& conn) {
    {
        std::unique_lock<std::mutex> locker(mutex_);
        conntion_.reset();
    }

    loop_->queueInLoop(std::bind(&TcpConnection::connectDestory, conn));
    if(retry_ && connect_) {
        conn_->restart();
    }
}

