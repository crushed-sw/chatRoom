#ifndef __EVENT_LOOP_HPP
#define __EVENT_LOOP_HPP

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "Timer.hpp"
#include "CurrentThread.hpp"

namespace crushed {
namespace net {

class Channel;
class Poller;

class EventLoop {
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    Timer pollReturnTime() const;

    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);

    void wakeup();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);

    bool isInLoopThread() const;

private:
    using ChannelList = std::vector<Channel*>;

    void handleRead();
    void doPendingFunctors();

    std::atomic_bool looping_;
    std::atomic_bool quit_;

    const pid_t threadId_;
    Timer pollerReturnTime_;
    std::unique_ptr<Poller> poller_;

    int wakeFd_;
    std::unique_ptr<Channel> wakeChannel_;

    ChannelList activeChannels_;

    std::atomic_bool callingPendingFunctors_;
    std::vector<Functor> pendingFunctors_;
    std::mutex mutex_;
};

} // namespace net
} // namespace crushed

#endif //__EVENT_LOOP_HPP
