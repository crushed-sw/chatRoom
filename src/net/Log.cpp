#include "../../include/net/Log.hpp"

#include <iostream>

using namespace crushed::net;

SyncQueue<std::string> Log::queue_(500);

Log::Log() : isFirst_(true), isStop_(false) {
    std::thread t(&Log::writeTask, this);
    t.detach();

    update();
}

Log::~Log() {
    queue_.put(ss_.str());
    isStop_ = true;
}

Log& Log::getInstance(level lev) {
    static Log logger;
    logger.lev_ = lev;
    return logger;
}

std::string Log::levelToString(const level& lev) {
    if(lev == level::INFO) {
        return "[info] ";
    } else if(lev == level::DEBUG) {
        return "[debug]";
    } else if(lev == level::WARN) {
        return "[warn] ";
    } else if(lev == level::ERROR) {
        return "[error]";
    } else if(lev == level::FATAL) {
        return "[fatal]";
    }
    return "";
}

Log& Log::operator<<(const std::string& str) {
    update();

    if(isFirst_) {
        ss_ << timer_.getNowString() << " " << levelToString(lev_) << " : ";
    }
    ss_ << str;

    isFirst_ = false;
    return *this;
}

Log& Log::operator<<(int i) {
    *this << std::to_string(i);
    return *this;
}

Log& Log::operator<<(double d) {
    *this << std::to_string(d);
    return *this;
}

Log& Log::operator<<(long int l) {
    *this << std::to_string(l);
    return *this;
}

Log& Log::operator<<(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    *this << ss.str();
    return *this;
}

Log& Log::operator<<(End end) {
    *this << "\n";

    std::string str = ss_.str();
    // std::cout << str;
    queue_.put(str);
    ss_.clear();
    ss_.str("");

    isFirst_ = true;
    return *this;
}

void Log::update() {
    long int millisecond;
    timer_.update();
    
    if(sourceDir_.empty()) {
        char buf[1024] = {};
        getcwd(buf, sizeof(buf));
        sourceDir_ = std::string(buf, strlen(buf)) + "/log";
        
        mkdir(sourceDir_.c_str(), 0775);
    }

    if(last_ != timer_.getDay()) {
        char buf[18];
        close(fd_);
        sprintf(buf, "/%04ld_%02ld_%02ld.log", timer_.getYear(), timer_.getMonth(), timer_.getDay());
        logFile_ = sourceDir_ + std::move(std::string(buf, strlen(buf)));
        last_ = timer_.getDay();
        fd_ = open(logFile_.c_str(), O_CREAT | O_RDWR | O_APPEND, 0664);
    }
}

void Log::writeTask() {
    while(!isStop_) {
        std::string str = "";
        queue_.take(str);
        write(fd_, str.c_str(), str.length());
    }
}
