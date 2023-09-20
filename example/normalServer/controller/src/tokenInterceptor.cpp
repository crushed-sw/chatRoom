#include "../include/tokenInterceptor.hpp"

bool TokenInterceptor::tokenInterceptor(crushed::http::Request& request, crushed::http::Response& response) {
    std::string token = request.getHeader()["Authorization"];

    try {
        return TokenUtil::checkToken(token, request.getParameter()["userid"]);
    } catch (std::exception e) {
        response.setCode(Codes::Unauthorized, "Unauthorized");
        return false;
    }
    return true;
}
