#include "../../include/net/EventLoop.hpp"
#include "../../include/net/Log.hpp"
#include "../../include/net/CurrentThread.hpp"
#include "../../include/net/Poller.hpp"
#include "../../include/net/Channel.hpp"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>

using namespace crushed::net;

int createEventFd() {
    int eventFd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

    if(eventFd < 0) {
        LogFatal << "eventfd() error: " << errno << LogEnd;
    }
    return eventFd;
}

__thread EventLoop* t_loopInThisThread = nullptr;
const int pollerTimeout_ = -1;

EventLoop::EventLoop() 
        : looping_(false)
        , quit_(false)
        , threadId_(currentThread::tid())
        , pollerReturnTime_()
        , poller_(Poller::newDefaultPoller(this))
        , wakeFd_(createEventFd())
        , wakeChannel_(new Channel(this, wakeFd_))
        , callingPendingFunctors_(false) {

    LogInfo << "event loop created in thread " << threadId_ << LogEnd;
    if(t_loopInThisThread) {
        LogFatal << "another eventloop exist in thread " << threadId_ << LogEnd;
    } else {
        t_loopInThisThread = this;
    }

    wakeChannel_->setReadCallBack(std::bind(&EventLoop::handleRead, this));
    wakeChannel_->enableRead();
}

EventLoop::~EventLoop() {
    wakeChannel_->disableAll();
    wakeChannel_->remove();
    close(wakeFd_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
    looping_ = true;
    quit_ = false;

    LogInfo << "eventloop start loop in " << threadId_ << LogEnd;

    while(!quit_) {
        activeChannels_.clear();
        pollerReturnTime_ = poller_->poll(pollerTimeout_, &activeChannels_);
        for(Channel* channel : activeChannels_) {
            channel->handleEvent(pollerReturnTime_);
        }
        doPendingFunctors();
    }

    looping_ = false;
}

void EventLoop::quit() {
    quit_ = true;
    if(!isInLoopThread()) {
        wakeup();
    }
}

Timer EventLoop::pollReturnTime() const {
    return pollerReturnTime_;
}

void EventLoop::runInLoop(Functor cb) {
    if(isInLoopThread()) {
        cb();
    } else {
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb) {
    {
        std::unique_lock<std::mutex> locker(mutex_);
        pendingFunctors_.emplace_back(cb);
    }

    if(!isInLoopThread() || callingPendingFunctors_) {
        wakeup();
    }
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    int len = write(wakeFd_, &one, sizeof(one));
    if(len != sizeof(one)) {
        LogError << "eventloop wakeup() write " << len << " bytes instead of " << static_cast<int>(sizeof(one)) << LogEnd;
    }
}

void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel) {
    poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel) {
    return poller_->hasChannel(channel);
}

bool EventLoop::isInLoopThread() const {
    return threadId_ == currentThread::tid();
}

void EventLoop::handleRead() {
    uint64_t one = 1;
    int len = read(wakeFd_, &one, sizeof(one));
    if(len != sizeof(one)) {
        LogError << "eventloop handleread() read " << len << " bytes instead of " << static_cast<int>(sizeof(one)) << LogEnd;
    }
}

void EventLoop::doPendingFunctors() {
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;

    {
        std::unique_lock<std::mutex> locker(mutex_);
        functors.swap(pendingFunctors_);
    }

    for(const Functor& func : functors) {
        func();
    }

    callingPendingFunctors_ = false;
}

