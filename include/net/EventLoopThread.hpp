#ifndef __EVENT_LOOP_THREAD_HPP
#define __EVENT_LOOP_THREAD_HPP

#include <mutex>
#include <condition_variable>

#include "Thread.hpp"

namespace crushed {
namespace net {

class EventLoop;

class EventLoopThread : NonCopyable {
public:
    using threadInitCallBack = std::function<void(EventLoop*)>;

    EventLoopThread(const threadInitCallBack& cb = threadInitCallBack(), const std::string& name = std::string());
    ~EventLoopThread();

    EventLoop* startLoop();

private:
    void threadFunc();

    EventLoop* loop_;
    bool exiting_;
    Thread thread_;

    std::mutex mutex_;
    std::condition_variable cond_;
    threadInitCallBack callback_;
};

} // namespace net
} // namespace net

#endif // __EVENT_LOOP_THREAD_HPP
