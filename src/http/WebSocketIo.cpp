#include "../../include/http/WebSocketIo.hpp"
#include "../../include/http/HttpServer.hpp"

#include <iostream>
#include <bitset>
#include <random>

using namespace crushed;
using namespace crushed::http;

WebSocketIo::WebSocketIo(HttpServer* httpServer, const net::TcpConnectionPtr& conn, const std::string& path) 
        : httpServer_(httpServer)
        , conn_(conn)
        , path_(path) {}

WebSocketIo::~WebSocketIo() {}

std::string WebSocketIo::getPath() const {
    return path_;
}

void WebSocketIo::setPath(const std::string& str) {
    path_ = str;
}

void WebSocketIo::send(const std::string& str) {
    conn_->send(setFrame(str));
}

void WebSocketIo::sendFrame(const std::string& str) {
    conn_->send(str);
}

WebSocketIo::WebSocketMessage WebSocketIo::getFrame(net::Buffer* buffer) {
    int allLen = 0;
    int headerSize = 2;

    unsigned char fin = 0;
    unsigned char opcode = 0;
    unsigned char mask = 0;
    uint64_t payloadLength = 0;

    std::vector<unsigned char> maskingKey;

    while(true) {
        if(buffer->readableBytes() >= headerSize) {
            std::string header = buffer->retrieveAsString(headerSize);
            allLen += headerSize;

            fin = (header[0] & 0x80) >> 7;
            opcode = header[0] & 0x0F;
            mask = (header[1] & 0x80) >> 7;
            payloadLength = header[1] & 0x7F;
            break;
        }
    }

    if (payloadLength == 126) {
        while(true) {
            if(buffer->readableBytes() >= 2) {
                std::string frame = buffer->retrieveAsString(2);
                payloadLength = ((frame[0] & 0x00000000000000ff) << 8) | (frame[1] & 0x00000000000000ff);
                break;
            }
        }
    } else if (payloadLength == 127) {
        while(true) {
            if(buffer->readableBytes() >= 8) {
                std::string frame = buffer->retrieveAsString(8);
                payloadLength = 0;
                for (int i = 0; i < 8; ++i) {
                    payloadLength = (payloadLength << 8) | (frame[i] & 0x00000000000000ff);
                }
                break;
            }
        }
    }

    if (mask) {
        while(true) {
            if(buffer->readableBytes() >= 4) {
                std::string frame = buffer->retrieveAsString(4);
                maskingKey.assign(frame.begin(), frame.end());
                break;
            }
        }
    }

    std::vector<unsigned char> payload(payloadLength);
    int index = 0;
    while(true) {
        if(payloadLength == 0)
            break;

        int readAble = buffer->readableBytes();
        if(readAble == 0)
            break;

        if(readAble > payloadLength) {
            std::string frame = buffer->retrieveAsString(payloadLength);
            std::copy(frame.begin(), frame.end(), payload.begin() + index);
            payloadLength = 0;
        } else {
            std::string frame = buffer->retrieveAsString(readAble);
            std::copy(frame.begin(), frame.end(), payload.begin() + index);
            index += readAble;
            payloadLength -= readAble;
        }
    }

    if (mask) {
        for (size_t i = 0; i < payload.size(); ++i) {
            payload[i] = payload[i] ^ maskingKey[i % 4];
        }
    }

    std::string message(payload.begin(), payload.end());

    bool isfinish = fin == 0x1;
    bool isping = opcode == 0x9;
    bool iscontinue = opcode == 0x0;
    bool isclose = opcode == 0x8;

    return WebSocketMessage{message, isfinish, isping, iscontinue, isclose};
}

std::string WebSocketIo::setFrame(const std::string& message) {
    std::vector<unsigned char> frame;

    frame.push_back(0x81);

    int payloadLength = message.length();
    if (payloadLength < 126) {
        frame.push_back(payloadLength);
    } else if (payloadLength <= 0xFFFF) {
        frame.push_back(126);
        frame.push_back(static_cast<unsigned char>((payloadLength >> 8) & 0xFF));
        frame.push_back(static_cast<unsigned char>(payloadLength & 0xFF));
    } else {
        frame.push_back(127);
        for(int i = 0; i != 4; ++i)
            frame.push_back(0);
        frame.push_back(static_cast<unsigned char>((payloadLength >> 24) & 0xFF));
        frame.push_back(static_cast<unsigned char>((payloadLength >> 16) & 0xFF));
        frame.push_back(static_cast<unsigned char>((payloadLength >> 8) & 0xFF));
        frame.push_back(static_cast<unsigned char>(payloadLength & 0xFF));
    }

    for (size_t i = 0; i < payloadLength; ++i) {
        frame.push_back(message[i]);
    }
    
    return std::string(frame.begin(), frame.end());
}

std::string WebSocketIo::buildPongFrame() {
    std::vector<unsigned char> frame;
    frame.push_back(0x8A);
    frame.push_back(0x00);
    return std::string(frame.begin(), frame.end());
}

std::string WebSocketIo::buildCloseFrame() {
    std::vector<unsigned char> frame;
    frame.push_back(0x88);
    frame.push_back(0x00);
    return std::string(frame.begin(), frame.end());
}


void WebSocketIo::close() {
    httpServer_->closeWebSocketConn(conn_);
}
