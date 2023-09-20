#ifndef __CURRENT_THREAD_HPP
#define __CURRENT_THREAD_HPP

#include <unistd.h>
#include <sys/syscall.h>

namespace crushed {
namespace net {
namespace currentThread {

extern __thread int t_cachedTid;

void cacheTid();

int tid();


} // namespace currentThread
} // namespace net
} // namespace crushed

#endif //__CURRENT_THREAD_HPP
