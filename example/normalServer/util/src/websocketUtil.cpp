#include "../include/websocketUtil.hpp"
#include <iostream>

std::unordered_map<std::string, crushed::http::WebSocketIoPtr> WebSocketUtil::roomsWebsocketMap_{};
std::unordered_map<std::string, std::set<crushed::http::WebSocketIoPtr>> WebSocketUtil::chatWebsocketMap_{};
std::unordered_map<std::string, std::set<std::pair<std::string, std::string>>> WebSocketUtil::onlineName_{};
std::unordered_map<std::string, crushed::http::WebSocketIoPtr> WebSocketUtil::onlineWebSocketMap_{};
std::mutex WebSocketUtil::mutex_{};
crushed::http::WebSocketIoPtr WebSocketUtil::nullPtr(std::make_shared<crushed::http::WebSocketIo>(nullptr, nullptr, "nullptr"));

const std::unordered_map<std::string, crushed::http::WebSocketIoPtr> WebSocketUtil::getRoomsWebSocket() {
    std::unique_lock<std::mutex> locker(mutex_);
    return roomsWebsocketMap_;
}

const crushed::http::WebSocketIoPtr WebSocketUtil::getRoomsWebSocket(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    return roomsWebsocketMap_[str];
}

void WebSocketUtil::removeRoomsWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    if(vec.size() != 2) {
        LogError << "setRoomsWebsocket() error" << LogEnd;
        return;
    }

    std::unique_lock<std::mutex> locker(mutex_);
    removeOnlineWebSocket(StringUtil::removeFirst(vec[1]));
    roomsWebsocketMap_.erase(vec[1]);
}

void WebSocketUtil::setRoomsWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    if(vec.size() != 2) {
        LogError << "setRoomsWebsocket() error" << LogEnd;
        return;
    }

    std::unique_lock<std::mutex> locker(mutex_);
    setOnlineWebSocket(StringUtil::removeFirst(vec[1]), io);
    roomsWebsocketMap_[vec[1]] = io;
}

const std::unordered_map<std::string, std::set<crushed::http::WebSocketIoPtr>> WebSocketUtil::getChatWebSocket() {
    std::unique_lock<std::mutex> locker(mutex_);
    return chatWebsocketMap_;
}

const std::set<crushed::http::WebSocketIoPtr> WebSocketUtil::getChatWebSocket(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    return chatWebsocketMap_[str];
}

const std::set<crushed::http::WebSocketIoPtr> WebSocketUtil::getChatWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    return getChatWebSocket(vec[1]);
}

const std::set<std::pair<std::string, std::string>> WebSocketUtil::getOnlineWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    std::unique_lock<std::mutex> locker(mutex_);
    return onlineName_[vec[1]];
}

void WebSocketUtil::removeChatWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    if(vec.size() != 4) {
        LogError << "setChatWebsocket() error" << LogEnd;
        return;
    }

    std::unique_lock<std::mutex> locker(mutex_);
    removeOnlineWebSocket(StringUtil::removeFirst(vec[2]));
    chatWebsocketMap_[vec[1]].erase(io);
    onlineName_[vec[1]].erase({std::string(vec[2].begin() + 1, vec[2].end()), std::string(vec[3].begin() + 1, vec[3].end())});
}

void WebSocketUtil::removeChatRoomWebSocket(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    chatWebsocketMap_.erase(str);
    removeOnlineWebSocket(StringUtil::removeFirst(str));
    onlineName_.erase(str);
}

void WebSocketUtil::setChatWebSocket(const crushed::http::WebSocketIoPtr& io) {
    auto vec = StringUtil::splitString(io->getPath());
    if(vec.size() != 4) {
        LogError << "setChatWebsocket() error" << LogEnd;
        return;
    }

    std::unique_lock<std::mutex> locker(mutex_);
    setOnlineWebSocket(StringUtil::removeFirst(vec[2]), io);
    onlineName_[vec[1]].insert({std::string(vec[2].begin() + 1, vec[2].end()), std::string(vec[3].begin() + 1, vec[3].end())});
    chatWebsocketMap_[vec[1]].insert(io);
}

const crushed::http::WebSocketIoPtr WebSocketUtil::getOnlineWebSocket(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    auto iter = onlineWebSocketMap_.find(str);
    if(iter == onlineWebSocketMap_.end()) {
        return nullPtr;
    }
    return iter->second;
}

void WebSocketUtil::setOnlineWebSocket(const std::string& str, const crushed::http::WebSocketIoPtr& io) {
    onlineWebSocketMap_[str] = io;
}

void WebSocketUtil::removeOnlineWebSocket(const std::string& str) {
    onlineWebSocketMap_.erase(str);
}

const crushed::http::WebSocketIoPtr WebSocketUtil::closeOnlineWebSocket(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    auto iter = onlineWebSocketMap_.find(str);
    if(iter != onlineWebSocketMap_.end()) {
        onlineWebSocketMap_.erase(str);
        return iter->second;
    }
    return nullPtr;
}

void WebSocketUtil::notifyAllRooms() {
    RoomService roomService_;
    Message<std::vector<RoomUser>> message(Codes::GetOk, roomService_.queryAllByName(), "");

    auto& roomsIo = getRoomsWebSocket();
    for(auto& io : roomsIo) {
        io.second->send(message.parse());
    }
}
