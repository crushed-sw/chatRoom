#ifndef __ROOMS_WEB_SOCKET_HPP
#define __ROOMS_WEB_SOCKET_HPP

#include "../../../../include/http/WebSocketIo.hpp"
#include "../../../../include/http/WebSocket.hpp"

#include "../../service/include/roomService.hpp"
#include "../../util/include/message.hpp"
#include "../../util/include/codes.hpp"
#include "../../util/include/websocketUtil.hpp"
#include "../../util/include/tokenUtil.hpp"

class RoomsWebSocket {
public:
    void roomOnOpen(crushed::http::WebSocketIoPtr& io);
    void roomOnMessage(crushed::http::WebSocketIoPtr& io, const std::string& str);
    void roomOnClose(crushed::http::WebSocketIoPtr& io);

private:
    RoomService service_;
};

#endif //__ROOMS_WEB_SOCKET_HPP
