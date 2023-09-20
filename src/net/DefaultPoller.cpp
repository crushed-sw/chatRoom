#include "../../include/net/Poller.hpp"
#include "../../include/net/EpollPoller.hpp"
#include "../../include/net/ServerApplication.hpp"

#include <stdlib.h>

using namespace crushed::net;

Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if(ServerApplication::getConfig().getValue("poller") == "poll") {
        return nullptr;
    } else {
        return new EpollPoller(loop);
    }
}
