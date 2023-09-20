#ifndef __TOKEN_INTERCEPTOR_HPP
#define __TOKEN_INTERCEPTOR_HPP

#include "../../../../include/http/HttpServer.hpp"
#include "../../../../thirdparty/json.hpp"

#include "../../util/include/tokenUtil.hpp"
#include "../../util/include/codes.hpp"
#include "../../util/include/message.hpp"

class TokenInterceptor {
public:
    bool tokenInterceptor(crushed::http::Request& request, crushed::http::Response& response);
};

#endif //__TOKEN_INTERCEPTOR_HPP
