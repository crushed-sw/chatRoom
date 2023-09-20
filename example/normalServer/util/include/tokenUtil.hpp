#ifndef __TOKEN_UTIL_HPP
#define __TOKEN_UTIL_HPP

#include "../../../../thirdparty/json.hpp"

#include "codes.hpp"
#include "stringUtil.hpp"

#include <mutex>
#include <random>
#include <string>
#include <vector>
#include <unordered_map>

class TokenUtil {
public:
    static std::string encodeToken(const std::string& str);
    static std::string decodeToken(const std::string& str);

    static std::unordered_map<std::string, std::string> getTokens();
    static std::string getToken(const std::string& str);

    static void setToken(const std::string& key, const std::string& value);

    static bool checkToken(const std::string& token, const std::string& userid);

private:
    static std::string parseStr_;
    static std::mutex mutex_;

    static std::unordered_map<std::string, std::string> tokens_;
};

#endif //__TOKEN_UTIL_HPP
