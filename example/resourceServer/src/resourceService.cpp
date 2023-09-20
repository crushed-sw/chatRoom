#include "../include/resourceService.hpp"

ResourceService::ResourceService() {
    getResource_.init();
}

void ResourceService::getResource(::google::protobuf::RpcController* controller,
                                  const ::crushed::ResourceRequest* request,
                                  ::crushed::ResourceResponse* response,
                                  ::google::protobuf::Closure* done) {
    try {
        std::string path = request->path();
        int code;
        std::string contentType;
        std::string message;
        std::string str = getResource_.getFile(code, contentType, message, path);

        crushed::ResourceResultCode* result = response->mutable_result();
        result->set_code(code);
        result->set_type(contentType);
        result->set_msg(message);
        response->set_responsemessage(str);

    } catch(std::exception e) {
        crushed::ResourceResultCode* result = response->mutable_result();
        result->set_code(400);
        result->set_msg("Bad request");
        response->set_responsemessage("");
    }

    done->Run();
}
