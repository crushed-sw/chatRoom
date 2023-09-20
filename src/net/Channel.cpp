#include "../../include/net/Channel.hpp"
#include "../../include/net/EventLoop.hpp"

using namespace crushed::net;

const int Channel::noneEvent_ = 0;
const int Channel::readEvent_ = EPOLLIN | EPOLLPRI | EPOLLET;
const int Channel::writeEvent_ = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false) {}

Channel::~Channel() {}

void Channel::handleEvent(Timer timer) {
    if(tied_) {
        std::shared_ptr<void> guard = tie_.lock();
        if(guard) {
            handleEventGuard(timer);
        }
    } else {
        handleEventGuard(timer);
    }
}

void Channel::setReadCallBack(ReadEventCallBack cb) {
    readCallBack_ = std::move(cb);
}

void Channel::setWriteCallBack(EventCallBack cb) {
    writeCallBack_ = std::move(cb);
}

void Channel::setErrorCallBack(EventCallBack cb) {
    errorCallBack_ = std::move(cb);
}

void Channel::setCloseCallBack(EventCallBack cb) {
    closeCallBack_ = std::move(cb);
}

void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}

int Channel::fd() {
    return fd_;
}

int Channel::events() {
    return events_;
}

void Channel::setRevents(int revents) {
    revents_ = revents;
}

bool Channel::isNoneEvent() const {
    return events_ == noneEvent_;
}

void Channel::enableRead() {
    events_ |= readEvent_;
    update();
}

void Channel::enableWrite() {
    events_ |= writeEvent_;
    update();
}

void Channel::disableRead() {
    events_ &= ~readEvent_;
    update();
}

void Channel::disableWrite() {
    events_ &= ~writeEvent_;
    update();
}

void Channel::disableAll() {
    events_ = noneEvent_;
    update();
}

bool Channel::isNonEvent() const {
    return events_ == noneEvent_;
}

bool Channel::isReadEvent() const {
    return events_ & readEvent_;
}

bool Channel::isWriteEvent() const {
    return events_ & writeEvent_;
}

int Channel::index() {
    return index_;
}

void Channel::setIndex(int index) {
    index_ = index;
}

EventLoop* Channel::ownLoop() {
    return loop_;
}

void Channel::remove() {
    loop_->removeChannel(this);
}

void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handleEventGuard(Timer timer) {
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
        if(closeCallBack_)
            closeCallBack_();

    if(revents_ & EPOLLERR)
        if(errorCallBack_)
            errorCallBack_();

    if(revents_ & (EPOLLIN | EPOLLPRI))
        if(readCallBack_)
            readCallBack_(timer);

    if(revents_ & EPOLLOUT)
        if(writeCallBack_)
            writeCallBack_();
}
