#ifndef __CHAT_WEB_SOCKET_HPP
#define __CHAT_WEB_SOCKET_HPP

#include "../../../../include/http/WebSocketIo.hpp"
#include "../../../../include/http/WebSocket.hpp"

#include "../../service/include/chatMessageService.hpp"
#include "../../service/include/roomService.hpp"
#include "../../util/include/message.hpp"
#include "../../util/include/codes.hpp"
#include "../../util/include/websocketUtil.hpp"
#include "../../util/include/tokenUtil.hpp"

class ChatWebSocket {
public:
    void chatOnOpen(crushed::http::WebSocketIoPtr& io);
    void chatOnMessage(crushed::http::WebSocketIoPtr& io, const std::string& str);
    void chatOnClose(crushed::http::WebSocketIoPtr& io);

private:
    void notifyAll(crushed::http::WebSocketIoPtr& io, const std::string& str);

    ChatMessageService chatService_;
    RoomService roomService_;
};

#endif //__CHAT_WEB_SOCKET_HPP

