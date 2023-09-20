#ifndef __CHANNEL_HPP
#define __CHANNEL_HPP

#include <functional>
#include <memory>

#include <sys/epoll.h>

#include "NonCopyable.hpp"
#include "Timer.hpp"

namespace crushed {
namespace net {

class EventLoop;

class Channel : public NonCopyable {
public:
    using EventCallBack = std::function<void()>;
    using ReadEventCallBack = std::function<void(Timer)>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void handleEvent(Timer timer);
    void setReadCallBack(ReadEventCallBack cb);
    void setWriteCallBack(EventCallBack cb);
    void setErrorCallBack(EventCallBack cb);
    void setCloseCallBack(EventCallBack cb);

    void tie(const std::shared_ptr<void>& obj);
    int fd();
    int events();
    void setRevents(int revents);
    bool isNoneEvent() const;

    void enableRead();
    void enableWrite();
    void disableRead();
    void disableWrite();
    void disableAll();

    bool isNonEvent() const;
    bool isReadEvent() const;
    bool isWriteEvent() const;

    int index();
    void setIndex(int index);

    EventLoop* ownLoop();
    void remove();

private:
    void update();
    void handleEventGuard(Timer timer);

    static const int noneEvent_;
    static const int readEvent_;
    static const int writeEvent_;

    EventLoop* loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    ReadEventCallBack readCallBack_;
    EventCallBack writeCallBack_;
    EventCallBack closeCallBack_;
    EventCallBack errorCallBack_;
};

} // namespace net
} // namespace crushed

#endif //__CHANNEL_HPP
