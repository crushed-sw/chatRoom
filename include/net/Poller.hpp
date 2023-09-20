#ifndef __POLLER_HPP
#define __POLLER_HPP

#include <vector>
#include <unordered_map>

#include "NonCopyable.hpp"
#include "Timer.hpp"

namespace crushed {
namespace net {

class Channel;
class EventLoop;

class Poller : public NonCopyable {
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    virtual ~Poller() = default;

    virtual Timer poll(int timeout, ChannelList* activeChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;

    bool hasChannel(Channel* channel) const;

    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;

private:
    EventLoop* ownerLoop_;
};

} // namespace net
} // namespace crushed

#endif //__POLLER_HPP
