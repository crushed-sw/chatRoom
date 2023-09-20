#ifndef __THREAD_HPP
#define __THREAD_HPP

#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <string>
#include <semaphore.h>

#include "NonCopyable.hpp"
#include "CurrentThread.hpp"

namespace crushed {
namespace net {

class Thread : public NonCopyable {
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc func, const std::string& name = "");
    ~Thread();

    void start();
    void join();

    bool started() const;
    pid_t tid() const;
    const std::string& name() const;

    static int numCreated();

private:
    void setDefaultName();

    bool started_;
    bool joined_;

    std::shared_ptr<std::thread> thread_;
    pid_t tid_;

    ThreadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
};

} // namespace net
} // namespace crushed

#endif //__THREAD_HPP
