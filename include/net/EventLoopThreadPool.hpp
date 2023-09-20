#ifndef __EVENT_LOOP_THREAD_POOL_HPP
#define __EVENT_LOOP_THREAD_POOL_HPP

#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "NonCopyable.hpp"

namespace crushed {
namespace net {

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : NonCopyable {
public:
    using threadInitCallBack = std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop* loop, const std::string& name);
    ~EventLoopThreadPool();

    void setThreadNum(int threadNum);
    void start(const threadInitCallBack& cb = threadInitCallBack());

    EventLoop* getNextLoop();
    std::vector<EventLoop*> getAllLoop();

    bool started() const;

    const std::string& name() const;

private:
    EventLoop* loop_;
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;

    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

} // namespace net
} // namespace crushed

#endif // __EVENT_LOOP_THREAD_POOL_HPP
