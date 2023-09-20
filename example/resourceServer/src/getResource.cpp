#include "../include/getResource.hpp"

GetResource::GetResource(const std::string& resource, int port, int threadNum)
        : resource_(resource)
        , port_(port)
        , threadNum_(threadNum) {}

GetResource::GetResource() {
    crushed::net::ServerConfig conf = crushed::net::ServerApplication::getInstance().getConfig();
    resource_ = conf.getValue("resource");

    if(resource_ == "") {
        char buf[512] = {};
        getcwd(buf, sizeof(buf));
        resource_ = std::string(buf, strlen(buf)) + "/resource";
    }

    std::string port = conf.getValue("port");
    if(port == "") {
        port = "9999";
    }
    port_ = atoi(port.c_str());

    std::string threadNum = conf.getValue("threadNum");
    if(threadNum == "") {
        threadNum = std::thread::hardware_concurrency();
    }
    threadNum_ = atoi(threadNum.c_str());
}

void GetResource::init() {
    initFiles(resource_);
}

std::string GetResource::getFile(int& code, std::string& type, std::string& msg, const std::string& path) {
    std::string filePath = path;
    if(path.back() == '/') {
        filePath += "index.html";
    }
    auto iter = files_.find(resource_ + filePath);

    if(iter != files_.end()) {
        code = 200;
        msg = "OK";
        std::string contentType = parseContentType(resource_ + filePath);

        if(contentType == "js")
            contentType = "text/javascript";
        else if(contentType == "css")
            contentType = "text/css";
        else if(contentType == "html")
            contentType = "text/html";
        else if(contentType == "ico")
            contentType = "image/x-icon";
        else
            contentType = "text/plain";
        
        type = contentType;
        return iter->second;
    } else {
        return notFound(code, type, msg);
    }
}

std::string GetResource::notFound(int& code, std::string& type, std::string& msg) {
    code = 404;
    msg = "Not Found";
    type = "text/html";
    
    std::stringstream ss;
    auto iter = files_.find(resource_ + "/notFound.html");
    if(iter != files_.end()) {
        return iter->second;
    }

    ss << "<!DOCTYPE html><html><head><title>404 Not Found</title><style>"
         << "body {font-family: Arial, sans-serif;background-color: #f1f1f1;}"
         << ".container {margin: 50px auto;width: 80%;max-width: 800px;text-align: center;}"
         << "h1 {font-size: 5em;color: #999;margin: 0;}"
         << "p {font-size: 1.5em;color: #666;margin: 0;}"
         << "</style></head><body><div class='container'><h1>404</h1>"
         << "<p>Sorry, the page you requested could not be found.</p>"
         << "</div></body></html>";
    return ss.str();
}

void GetResource::initFiles(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if(dir == nullptr)
        throw std::runtime_error("resource dir can't open");

    dirent* entry = nullptr;
    while((entry = readdir(dir)) != nullptr) {
        if(entry->d_name[0] == '.')
            continue;

        std::string filePath = path + "/" + entry->d_name;
        struct stat st = {};
        if(stat(filePath.c_str(), &st) == -1)
            continue;

        if(S_ISDIR(st.st_mode)) {
            initFiles(filePath);
        } else if(S_ISREG(st.st_mode)) {
            std::stringstream ss;
            ss << std::fstream(filePath).rdbuf();
            files_[filePath] = ss.str();
        }
    }

    closedir(dir);
}

std::string GetResource::parseContentType(const std::string& str) {
    auto iter = str.find_last_of('.');
    if(iter == -1) {
        return "";
    }

    return str.substr(iter + 1, str.size() - iter);
}
