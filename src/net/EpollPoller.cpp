#include "../../include/net/EpollPoller.hpp"
#include "../../include/net/Channel.hpp"

using namespace crushed::net;

const int new_ = -1;
const int added_ = 1;
const int deleted_ = 2;

EpollPoller::EpollPoller(EventLoop* loop) : Poller(loop), epollFd_(epoll_create1(EPOLL_CLOEXEC)), events_(initEventsSize) {
    if(epollFd_ < 0) {
        LogFatal << "epoll_create error" << LogEnd;
    }
}

EpollPoller::~EpollPoller() {
    close(epollFd_);
}

Timer EpollPoller::poll(int timeout, ChannelList* activeChannels) {
    int numEvent = epoll_wait(epollFd_, &*events_.begin(), static_cast<int>(events_.size()), timeout);
    int saveErrno = errno;

    if(numEvent > 0) {
        fillActiveChannels(numEvent, activeChannels);
        if(numEvent == events_.size()) {
            events_.resize(events_.size() * 2);
        }
    } else if(numEvent == 0) {
        LogError << "epoll_wait() timeout" << LogEnd;
    } else {
        if(saveErrno != EINTR) {
            errno = saveErrno;
        }
        LogError << "epoll_wait() error : " << saveErrno << LogEnd;
    }

    return Timer();
}

void EpollPoller::updateChannel(Channel* channel) {
    int index = channel->index();
    if(index == new_ || index == deleted_) {
        if(index == new_) {
            int fd = channel->fd();
            channels_[fd] = channel;
        }

        channel->setIndex(added_);
        update(EPOLL_CTL_ADD, channel);
    } else {
        int fd = channel->fd();
        if(channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->setIndex(deleted_);
        } else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EpollPoller::removeChannel(Channel* channel) {
    int fd = channel->fd();
    channels_.erase(fd);

    if(channel->index() == added_) {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->setIndex(new_);
}

void EpollPoller::fillActiveChannels(int num, ChannelList* activeChannels) const {
    for(int i = 0; i != num; ++i) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->setRevents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

void EpollPoller::update(int operation, Channel* channel) {
    int fd = channel->fd();
    epoll_event event = {};
    event.events = channel->events();
    event.data.ptr = channel;

    int ret = epoll_ctl(epollFd_, operation, fd, &event);
    if(ret  < 0) {
        if(operation == EPOLL_CTL_DEL) {
            LogError << "epoll_ctl delete error : " << errno;
        } else {
            LogFatal << "epoll_ctl error : " << errno;
        }
    }
}
