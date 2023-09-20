#include "../include/loginController.hpp"


std::string LoginController::checkLogin(crushed::http::Request& request, crushed::http::Response& response) {
    auto parameters = request.getParameter();
    std::string userid = parameters["userid"];

    if(userid == "") {
        Message<std::string> message(Codes::LoginParaNull, "", "参数为空");
        return message.parse();
    }

    Message<std::string> message(Codes::GetOk, "", "");
    return message.parse();
}

std::string LoginController::login(crushed::http::Request& request, crushed::http::Response& response) {
    auto parameters = request.getParameter();
    std::string userid = parameters["userid"];
    std::string password = parameters["password"];

    if(userid == "" || password == "") {
        std::cout << "null" << std::endl;
        Message<std::string> message(Codes::LoginParaNull, "", "参数为空");
        return message.parse();
    }

    User user = service_.query(std::atoi(userid.c_str()));

    if(user.getUserid() == -1 || user.getUsername() == "" || user.getPassword() != password) {
        Message<std::string> message(Codes::LoginParaError, "", "用户名或密码错误");
        LogInfo << userid << " login error, password error" << LogEnd;
        return message.parse();
    }

    LogInfo << userid << " login success" << LogEnd;
    
    auto socket = WebSocketUtil::closeOnlineWebSocket(userid);
    if(socket->getPath() != "nullptr") {
        socket->close();
    }

    nlohmann::json json;
    json["userid"] = userid;

    std::string token = TokenUtil::encodeToken(json.dump());
    TokenUtil::setToken(userid, token);

    user.setToken(token);
    user.setPassword("");

    Message<User> message(Codes::LoginOk, user, "登陆成功");
    return message.parse();
}

std::string LoginController::registe(crushed::http::Request& request, crushed::http::Response& response) {
    auto parameters = request.getParameter();
    std::string userid = parameters["userid"];
    std::string username = parameters["username"];
    std::string password = parameters["password"];

    if(username == "" || password == "") {
        Message<std::string> message(Codes::RegisterParaNull, "", "参数错误");
        return message.parse();
    }

    User user = service_.query(std::atoi(userid.c_str()));

    
    if(user.getUserid() != -1 || user.getUsername() != "") {
        Message<std::string> message(Codes::RegisterParaExisted, "", "用户名已存在");
        LogInfo << username << " register error, username alrerady exist" << LogEnd;
        return message.parse();
    }

    user.setUserid(std::atoi(userid.c_str()));
    user.setUsername(username);
    user.setPassword(password);
    service_.insert(user);

    LogInfo << userid << " register success" << LogEnd;
    
    Message<User> message(Codes::RegisterOk, user, "注册成功");
    return message.parse();
}
