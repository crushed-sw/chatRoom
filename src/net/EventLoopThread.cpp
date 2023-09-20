#include "../../include/net/EventLoopThread.hpp"
#include "../../include/net/EventLoop.hpp"

using namespace crushed::net;

EventLoopThread::EventLoopThread(const threadInitCallBack& cb, const std::string& name)
        : loop_(nullptr)
        , exiting_(false)
        , thread_(std::bind(&EventLoopThread::threadFunc, this), name)
        , callback_(cb) {}

EventLoopThread::~EventLoopThread() {
    exiting_ = true;
    if(loop_ != nullptr) {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::startLoop() {
    thread_.start();
    EventLoop* loop = nullptr;

    {
        std::unique_lock<std::mutex> locker(mutex_);
        while(loop_ == nullptr) {
            cond_.wait(locker);
        }
        loop = loop_;
    }

    return loop;
}

void EventLoopThread::threadFunc() {
    EventLoop loop;
    if(callback_) {
        callback_(&loop);
    }

    {
        std::unique_lock<std::mutex> locker(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }

    loop.loop();

    std::unique_lock<std::mutex> locker(mutex_);
    loop_ = nullptr;
}
