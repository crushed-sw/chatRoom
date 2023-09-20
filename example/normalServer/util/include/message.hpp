#ifndef __MESSAGE_HPP
#define __MESSAGE_HPP

#include "../../../../thirdparty/json.hpp"

#include <string>
#include <sstream>

template <typename T>
class Message {
public:
    Message(int code, T data, const std::string& msg);
    std::string parse();

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Message, code, data, msg);

private:
    int code;
    T data;
    std::string msg;
};

template <typename T>
Message<T>::Message(int code, T data, const std::string& msg) 
        : code(code)
        , data(data)
        , msg(msg) {}

template <typename T>
std::string Message<T>::parse() {
    nlohmann::json json;
    to_json(json, *this);
    return json.dump();
}

#endif //__MESSAGE_HPP
