#include <string>
#include <iostream>
#include <vector>

std::string parseStr_("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&'()*+,-./:;<=>?@[]^_`{|}~");
std::string mask_;
std::vector<int> vec;

std::string encodeToken(const std::string& str) {
    std::string ciphertext;
    for (size_t i = 0; i < str.length(); ++i) {
        ciphertext.push_back(parseStr_[(parseStr_.find(str[i]) + vec[i % vec.size()]) % parseStr_.size()]);
    }
    return ciphertext;
}

std::string decodeToken(const std::string& str) {
    std::string plaintext;
    for (size_t i = 0; i < str.length(); ++i) {
        plaintext.push_back(parseStr_[(parseStr_.find(str[i]) - vec[i % vec.size()] + parseStr_.size()) % parseStr_.size()]);
    }
    return plaintext;
}

void parseMask() {
    for(int i = 0; i != mask_.size(); ++i) {
        vec.push_back(parseStr_.find(mask_[i]));
    }
}

int main() {
    mask_ = "Crushed";
    parseMask();
    std::string str = encodeToken("{nihao:haha}");
    std::cout << str << std::endl;
    std::cout << decodeToken(str) << std::endl;
}
