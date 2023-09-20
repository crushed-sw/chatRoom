#ifndef __STRING_UTIL_HPP
#define __STRING_UTIL_HPP

#include <string>
#include <vector>

class StringUtil {
public:
    static std::vector<std::string> splitString(const std::string& str);
    static std::string getUserIdFromRoomPath(const std::string& str);
    static std::string getUserIdFromChatPath(const std::string& str);
    static std::string removeFirst(const std::string& str);
};

#endif //__STRING_UTIL_HPP
