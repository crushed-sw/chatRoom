#ifndef __LOG_HPP
#define __LOG_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <thread>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "SyncQueue.hpp"
#include "Timer.hpp"

namespace crushed {
namespace net {

class Log {
public:
    enum level {INFO, DEBUG, WARN, ERROR, FATAL};
    struct End {};

    Log();
    ~Log();

    static Log& getInstance(level lev);

    Log& operator<<(const std::string& t);
    Log& operator<<(int i);
    Log& operator<<(double d);
    Log& operator<<(long int l);
    Log& operator<<(void* ptr);
    Log& operator<<(End end);

    std::string levelToString(const level& lev);
    void update();

private:
    void changeLog();
    void writeTask();

    std::string sourceDir_;
    std::string logFile_;
    long int last_;
    Timer timer_;
    level lev_;
    int fd_;

    static SyncQueue<std::string> queue_;
    std::mutex mutex_;

    std::stringstream ss_;
    bool isFirst_;
    bool isStop_;
};

#define LogInfo crushed::net::Log::getInstance(crushed::net::Log::INFO)
#define LogDebug crushed::net::Log::getInstance(crushed::net::Log::DEBUG)
#define LogWarn crushed::net::Log::getInstance(crushed::net::Log::WARN)
#define LogError crushed::net::Log::getInstance(crushed::net::Log::ERROR)
#define LogFatal crushed::net::Log::getInstance(crushed::net::Log::FATAL)
#define LogEnd crushed::net::Log::End{}

} // namespace net
} // namespace crushed

#endif //__LOG_HPP
