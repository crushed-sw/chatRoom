#ifndef __WEB_SOCKET_UTIL_HPP
#define __WEB_SOCKET_UTIL_HPP

#include "../../../../include/http/WebSocket.hpp"
#include "../../../../include/http/WebSocketIo.hpp"
#include "../../../../include/net/Log.hpp"

#include "../../util/include/stringUtil.hpp"
#include "../../util/include/codes.hpp"
#include "../../util/include/message.hpp"
#include "../../service/include/roomService.hpp"
#include "../../entity/include/roomUser.hpp"

#include "stringUtil.hpp"

#include <mutex>
#include <unordered_map>
#include <set>
#include <string>

class WebSocketUtil {
public:
    static const std::unordered_map<std::string, crushed::http::WebSocketIoPtr> getRoomsWebSocket();
    static const crushed::http::WebSocketIoPtr getRoomsWebSocket(const std::string& str);

    static void removeRoomsWebSocket(const crushed::http::WebSocketIoPtr& io);
    static void setRoomsWebSocket(const crushed::http::WebSocketIoPtr& io);

    static const std::unordered_map<std::string, std::set<crushed::http::WebSocketIoPtr>> getChatWebSocket();
    static const std::set<crushed::http::WebSocketIoPtr> getChatWebSocket(const std::string& str);
    static const std::set<crushed::http::WebSocketIoPtr> getChatWebSocket(const crushed::http::WebSocketIoPtr& io);

    static void removeChatWebSocket(const crushed::http::WebSocketIoPtr& io);
    static void removeChatRoomWebSocket(const std::string& str);
    static void setChatWebSocket(const crushed::http::WebSocketIoPtr& io);

    static const std::set<std::pair<std::string, std::string>> getOnlineWebSocket(const crushed::http::WebSocketIoPtr& io);

    static const crushed::http::WebSocketIoPtr getOnlineWebSocket(const std::string& str);
    static void setOnlineWebSocket(const std::string& str, const crushed::http::WebSocketIoPtr& io);
    static void removeOnlineWebSocket(const std::string& str);
    static const crushed::http::WebSocketIoPtr closeOnlineWebSocket(const std::string& str);

    static void notifyAllRooms();

private:
    static std::unordered_map<std::string, crushed::http::WebSocketIoPtr> roomsWebsocketMap_;
    static std::unordered_map<std::string, std::set<crushed::http::WebSocketIoPtr>> chatWebsocketMap_;
    static std::unordered_map<std::string, std::set<std::pair<std::string, std::string>>> onlineName_;
    static std::unordered_map<std::string, crushed::http::WebSocketIoPtr> onlineWebSocketMap_;

    static std::mutex mutex_;

    static crushed::http::WebSocketIoPtr nullPtr;
};

#endif //__WEB_SOCKET_UTIL_HPP
