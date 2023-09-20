#ifndef __NET_BUFFER_HPP
#define __NET_BUFFER_HPP

#include <vector>
#include <string>

#include <sys/uio.h>
#include <unistd.h>

namespace crushed {
namespace net {

class Buffer {
public:
    static const std::size_t cheapPrepared = 8;
    static const std::size_t initSize = 2048;

    explicit Buffer(std::size_t size = initSize);

    std::size_t readableBytes() const;
    std::size_t writableBytes() const;
    std::size_t preparedBytes() const;

    const char* writeIndex() const;

    const char* peek() const;
    void retrieve(std::size_t size);
    void retrieve(const char* end);
    void retrieveAll();
    std::string retrieveAllAsString();
    std::string retrieveAsString(std::size_t size);

    void ensureWriteAbleBytes(std::size_t size);
    void append(const char* data, std::size_t len);
    std::size_t readFd(int fd, int& saveErrno);
    std::size_t writeFd(int fd, int& saveErrno);

private:
    char* begin();
    const char* begin() const;

    void makeSpace(std::size_t size);

    std::vector<char> buffer_;
    std::size_t readIndex_;
    std::size_t writeIndex_;
};

} // namespace net
} // namespace crushed

#endif //)__NET_BUFFER_HPP
