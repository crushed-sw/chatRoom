#ifndef __REQUEST_HPP
#define __REQUEST_HPP

#include <string>
#include <map>

#include "../net/Buffer.hpp"
#include "../../thirdparty/json.hpp"

namespace crushed {
namespace http {

class Request {
public:
    enum Method {GET, POST, PUT, DELETE, NONE};

    Request(net::Buffer* buffer);
    
    Request::Method stringToMethod(const std::string& str);
    Request::Method getMethod();
    std::string getPath();
    std::string getVersion();
    std::map<std::string, std::string> getHeader();
    std::map<std::string, std::string> getParameter();

private:
    enum State {REQUEST, HEADER, BODY, FINISH};

    void getContent(net::Buffer* buffer);

    bool parseRequest(const std::string& str);
    void parseHeader(const std::string& str);
    void parseBody(const std::string& str);

    void parsePostParameter();
    void parseGetParameter();

    void parseParameter(const std::string& str);
    void parseJson(const std::string& str);
    void parseUrlencoded(const std::string& str);

    void clearStream();

    std::string method_;
    std::string path_;
    std::string version_;

    State state_;

    std::stringstream localss_;

    std::map<std::string, std::string> headers_;
    std::map<std::string, std::string> parameters_;

    int contentLength_;
    std::stringstream content_;
};

} // namespace http
} // namespace crushed

#endif //__REQUEST_HPP
