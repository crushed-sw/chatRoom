#ifndef __EPOLL_POLLER_HPP
#define __EPOLL_POLLER_HPP

#include "Poller.hpp"
#include "Log.hpp"

#include <vector>

#include <sys/epoll.h>
#include <unistd.h>

namespace crushed {
namespace net {

class EpollPoller : public Poller {
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller() override;

    Timer poll(int timeout, ChannelList* activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channel) override;

private:
    using eventList = std::vector<epoll_event>;

    void fillActiveChannels(int num, ChannelList* activeChannels) const;
    void update(int operation, Channel* channel);

    static const int initEventsSize = 16;

    int epollFd_;
    eventList events_;
};

} // namespace net
} // namespace crushed

#endif //__EPOLL_POLLER_HPP
