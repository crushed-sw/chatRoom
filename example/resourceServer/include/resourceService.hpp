#ifndef __RESOURCE_SERVICE_HPP
#define __RESOURCE_SERVICE_HPP

#include "resource.pb.h"
#include "getResource.hpp"

class ResourceService : public crushed::ResourceService {
public:
    ResourceService();

    void getResource(::google::protobuf::RpcController* controller,
                     const ::crushed::ResourceRequest* request,
                     ::crushed::ResourceResponse* response,
                     ::google::protobuf::Closure* done) override;

private:
    GetResource getResource_;
};

#endif //__RESOURCE_SERVICE_HPP
