#include "../../include/net/CurrentThread.hpp"

namespace crushed {
namespace net {
namespace currentThread {

__thread int t_cachedTid = 0;

void cacheTid() {
    if(t_cachedTid == 0) {
        t_cachedTid = static_cast<pid_t>(syscall(SYS_gettid));
    }
}

int tid() {
    if(__builtin_expect(t_cachedTid == 0, 0)) {
        cacheTid();
    }
    return t_cachedTid;
}

}
}
}
