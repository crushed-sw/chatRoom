#include "../include/tokenUtil.hpp"
#include <iostream>

std::string TokenUtil::parseStr_("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&'()*+,-./:;<=>?@[]^_`{|}~\"\\");
std::mutex TokenUtil::mutex_{};
std::unordered_map<std::string, std::string> TokenUtil::tokens_{};

std::string TokenUtil::encodeToken(const std::string& str) {
    std::vector<int> vec;
    std::string mask;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, parseStr_.size() - 1);
    for(int i = 0; i != 5; ++i) {
        int value = dist(gen);
        vec.push_back(value);
        mask.push_back(parseStr_[value]);
    }

    std::string ciphertext;
    for (size_t i = 0; i < str.length(); ++i) {
        ciphertext.push_back(parseStr_[(parseStr_.find(str[i]) + vec[i % vec.size()]) % parseStr_.size()]);
    }

    return mask + ciphertext;
}

std::string TokenUtil::decodeToken(const std::string& str) {
    std::vector<int> vec;
    std::string mask(str.begin(), str.begin() + 5);

    for(char c : mask) {
        vec.push_back(parseStr_.find(c));
    }

    std::string plaintext;
    for (size_t i = 5; i < str.length(); ++i) {
        plaintext.push_back(parseStr_[(parseStr_.find(str[i]) - vec[i % vec.size()] + parseStr_.size()) % parseStr_.size()]);
    }
    return plaintext;
}

std::unordered_map<std::string, std::string> TokenUtil::getTokens() {
    std::unique_lock<std::mutex> locker(mutex_);
    return tokens_;
}

std::string TokenUtil::getToken(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    return tokens_[str];
}

void TokenUtil::setToken(const std::string& key, const std::string& value) {
    std::unique_lock<std::mutex> locker(mutex_);
    tokens_[key] = value;
}

bool TokenUtil::checkToken(const std::string& token, const std::string& userid) {
    nlohmann::json json = nlohmann::json::parse(decodeToken(token));
    if(json["userid"] != userid) {
        return false;
    }

    if(token != tokens_[userid]) {
        return false;
    }
    return true;
}
