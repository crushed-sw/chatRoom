#include "../../include/net/Buffer.hpp"

using namespace crushed::net;


Buffer::Buffer(std::size_t size) : buffer_(cheapPrepared + size), readIndex_(cheapPrepared), writeIndex_(cheapPrepared) {}


std::size_t Buffer::readableBytes() const {
    return writeIndex_ - readIndex_;
}

std::size_t Buffer::writableBytes() const {
    return buffer_.size() - writeIndex_;
}

std::size_t Buffer::preparedBytes() const {
    return readIndex_;
}

const char* Buffer::writeIndex() const {
    return begin() + writeIndex_;
}

const char* Buffer::peek() const {
    return begin() + readIndex_;
}

void Buffer::retrieve(std::size_t size) {
    if(size < readableBytes()) {
        readIndex_ += size;
    } else {
        retrieveAll();
    }
}

void Buffer::retrieve(const char* end) {
    retrieve(end - peek());
}

void Buffer::retrieveAll() {
    readIndex_ = writeIndex_ = cheapPrepared;
}

std::string Buffer::retrieveAllAsString() {
    return retrieveAsString(readableBytes());
}

std::string Buffer::retrieveAsString(std::size_t size) {
    std::string result(peek(), size);
    retrieve(size);
    return result;
}

void Buffer::ensureWriteAbleBytes(std::size_t size) {
    if(writableBytes() < size) {
        makeSpace(size);
    }
}

void Buffer::append(const char* data, std::size_t len) {
    ensureWriteAbleBytes(len);
    std::copy(data, data + len, begin() + writeIndex_);
    writeIndex_ += len;
}

std::size_t Buffer::readFd(int fd, int& saveErrno) {
    char buf[65536] = {};
    iovec vec[2];
    const std::size_t writable = writableBytes();

    vec[0].iov_base = begin() + writeIndex_;
    vec[0].iov_len = writable;

    vec[1].iov_base = buf;
    vec[1].iov_len = sizeof(buf);

    const int iovcnt = (writable < sizeof(buf)) ? 2 : 1;
    const std::size_t len = readv(fd, vec, iovcnt);

    if(len < 0) {
        saveErrno = errno;
    } else if (len <= writable) {
        writeIndex_ += len;
    } else {
        writeIndex_ = buffer_.size();
        append(buf, len - writable);
    }

    return len;
}


std::size_t Buffer::writeFd(int fd, int& saveErrno) {
    std::size_t len = write(fd, peek(), readableBytes());
    if(len < 0) {
        saveErrno = errno;
    }
    return len;
}

char* Buffer::begin() {
    return buffer_.data();
}

const char* Buffer::begin() const {
    return buffer_.data();
}

void Buffer::makeSpace(std::size_t size) {
    if(writableBytes() + preparedBytes() < size + cheapPrepared) {
        buffer_.resize(writeIndex_ + size);
    } else {
        std::size_t readable = readableBytes();
        std::copy(begin() + readIndex_, begin() + writeIndex_, begin() + cheapPrepared);
        readIndex_ = cheapPrepared;
        writeIndex_ = readIndex_ + readable;
    }
}
