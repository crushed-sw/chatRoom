#include "../include/stringUtil.hpp"

std::vector<std::string> StringUtil::splitString(const std::string& str) {
    std::vector<std::string> ans;

    auto slow = str.begin();
    auto fast = str.begin();
    while(fast != str.end()) {
        if(*fast == '/' && fast != slow) {
            ans.emplace_back(slow, fast);
            slow = fast;
        }
        fast++;
    }
    ans.emplace_back(slow, fast);

    return ans;
}

std::string StringUtil::getUserIdFromRoomPath(const std::string& str) {
    auto vec = splitString(str);
    return {vec.back().begin() + 1, vec.back().end()};
}

std::string StringUtil::getUserIdFromChatPath(const std::string& str) {
    auto vec = splitString(str);
    return {vec[2].begin() + 1, vec[2].end()};
}

std::string StringUtil::removeFirst(const std::string& str) {
    return {str.begin() + 1, str.end()};
}
