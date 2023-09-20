#ifndef __GET_RESOURCE_HPP
#define __GET_RESOURCE_HPP

#include "../../../include/net/ServerApplication.hpp"

#include <unordered_map>
#include <fstream>
#include <dirent.h>

class GetResource {
public:
    GetResource(const std::string& resource, int port, int threadNum);
    GetResource();

    void init();
    std::string getFile(int& code, std::string& type, std::string& msg, const std::string& path);

private:
    std::string notFound(int& code, std::string& type, std::string& msg);

    void initFiles(const std::string& path);
    std::string parseContentType(const std::string& str);

    std::unordered_map<std::string, std::string> files_;

    std::string resource_;
    int port_;
    int threadNum_;
};

#endif //__GET_RESOURCE_HPP
