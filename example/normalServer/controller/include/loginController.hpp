#ifndef __LOGIN_CONROLLER_HPP
#define __LOGIN_CONROLLER_HPP

#include "../../../../include/http/HttpServer.hpp"
#include "../../../../include/net/Log.hpp"
#include "../../../../thirdparty/json.hpp"

#include "../../util/include/message.hpp"
#include "../../util/include/codes.hpp"
#include "../../util/include/tokenUtil.hpp"
#include "../../util/include/websocketUtil.hpp"
#include "../../entity/include/user.hpp"
#include "../../service/include/userService.hpp"

#include <string>
#include <map>

class LoginController {
public:
    std::string checkLogin(crushed::http::Request& request, crushed::http::Response& response);
    std::string login(crushed::http::Request& request, crushed::http::Response& response);
    std::string registe(crushed::http::Request& request, crushed::http::Response& response);

private:
    UserService service_;
};

#endif //__LOGIN_CONROLLER_HPP
