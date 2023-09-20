#include "../../include/net/EventLoopThreadPool.hpp"
#include "../../include/net/EventLoopThread.hpp"

using namespace crushed::net;

EventLoopThreadPool::EventLoopThreadPool(EventLoop* loop, const std::string& name)
        : loop_(loop)
        , name_(name)
        , started_(false)
        , numThreads_(0)
        , next_(0) {}

EventLoopThreadPool::~EventLoopThreadPool() {}

void EventLoopThreadPool::setThreadNum(int threadNum) {
    numThreads_ = threadNum;
}

void EventLoopThreadPool::start(const threadInitCallBack& cb) {
    started_ = true;
    for(int i = 0; i < numThreads_; ++i) {
        char buf[name_.size() + 32];
        sprintf(buf, "%s%d", name_.c_str(), i);
        EventLoopThread* t = new EventLoopThread(cb, buf);
        threads_.emplace_back(std::unique_ptr<EventLoopThread>(t));
        loops_.emplace_back(t->startLoop());
    }

    if(numThreads_ == 0 && cb) {
        cb(loop_);
    }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
    EventLoop* loop = loop_;

    if(!loops_.empty()) {
        loop = loops_[next_];
        next_++;
        if(next_ == loops_.size()) {
            next_ = 0;
        }
    }

    return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoop() {
    if(loops_.empty())
        return std::vector<EventLoop*>(1, loop_);
    return loops_;
}

bool EventLoopThreadPool::started() const {
    return started_;
}

const std::string& EventLoopThreadPool::name() const {
    return name_;
}

