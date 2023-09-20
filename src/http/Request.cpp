#include "../../include/http/Request.hpp"

#include <cstring>
#include <algorithm>
#include <iostream>
#include <regex>

using namespace crushed::http;

Request::Request(net::Buffer* buffer) {
    contentLength_ = 0;
    state_ = REQUEST;
    char crlf[] = "\r\n";

    while(state_ != FINISH) {
        const char* lineEnd = std::search(buffer->peek(), buffer->writeIndex(), crlf, crlf + 2);
        std::string line(buffer->peek(), lineEnd);

        switch(state_) {
            case REQUEST:
                if(!parseRequest(line)) {
                    return;
                }
                break;
            case HEADER:
                parseHeader(line);
                break;
            case BODY:
                getContent(buffer);
                parseBody(content_.str());
                break;
            default:
                break;
        }

        if(lineEnd == buffer->writeIndex())
            break;

        buffer->retrieve(lineEnd + 2);
    }
}

void Request::getContent(net::Buffer* buffer) {
    while(buffer->readableBytes() < contentLength_) {}
    content_ << std::string(buffer->peek(), contentLength_);
}

bool Request::parseRequest(const std::string& str) {
    std::regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch mach;
    if(std::regex_match(str, mach, patten)) {
        method_ = mach[1];
        path_ = mach[2];
        version_ = mach[3];
        state_ = HEADER;

        parseGetParameter();

        return true;
    }
    return false;
}

void Request::parseHeader(const std::string& str) {
    std::regex patten("^([^:]*): ?(.*)$");
    std::smatch mach;
    if(std::regex_match(str, mach, patten)) {
        headers_.insert({mach[1], mach[2]});
    } else {
        if(headers_.find("Content-Length") != headers_.end()) {
            contentLength_ = std::atoi(headers_["Content-Length"].c_str());
        }
        state_ = BODY;
    }
}

void Request::parseBody(const std::string& str) {
    std::string type = headers_["Content-Type"];
    state_ = FINISH;

    if(type.find("application/x-www-form-urlencoded") != -1) {
        parseUrlencoded(str);
    } else if(type.find("application/json") != -1) {
        parseJson(str);
    }
}

void Request::parseParameter(const std::string& str) {
    std::string line = str;
    auto iter = std::find(line.begin(), line.end(), '=');
    if(iter != line.end())
        *iter = ' ';

    std::stringstream ss(line);
    std::string key = "";
    std::string value = "";
    ss >> key >> value;

    parameters_.insert({key, value});
}

void Request::parseUrlencoded(const std::string& str) {
    clearStream();
    localss_.str(str);
    std::string kv = {};
    while(std::getline(localss_, kv, '&')) {
        parseParameter(kv);
    }
}

void Request::parseJson(const std::string& str) {
    nlohmann::json json = nlohmann::json::parse(str);
    for(auto iter = json.begin(); iter != json.end(); ++iter) {
        parameters_.insert({iter.key(), iter.value()});
    }
}

void Request::parseGetParameter() {
    auto iter = std::find(path_.begin(), path_.end(), '?');
    if(iter == path_.end())
        return;

    *iter = ' ';
        
    clearStream();
    localss_.str(path_);
    std::string parameter = {};
    localss_ >> path_ >> parameter;

    clearStream();
    localss_.str(parameter);
    std::string kv = {};
    while(std::getline(localss_, kv, '&'))
        parseParameter(kv);
}

void Request::clearStream() {
    localss_.str("");
    localss_.clear();
}

Request::Method Request::stringToMethod(const std::string& str) {
    if(str == "GET") {
        return GET;
    } else if(str == "POST") {
        return POST;
    } else if(str == "PUT") {
        return PUT;
    } else if(str == "DELETE") {
        return DELETE;
    }
    return NONE;
}

Request::Method Request::getMethod() {
    return stringToMethod(method_);
}

std::string Request::getPath() {
    return path_;
}

std::string Request::getVersion() {
    return version_;
}

std::map<std::string, std::string> Request::getHeader() {
    return headers_;
}

std::map<std::string, std::string> Request::getParameter() {
    return parameters_;
}
