#ifndef __RPC_CONTROLLER_HPP
#define __RPC_CONTROLLER_HPP

#include <google/protobuf/service.h>

namespace crushed {
namespace rpc {

class RpcController : public google::protobuf::RpcController {
public:
    RpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);
private:
    bool failed_;
    std::string errorMessage_;
};

} // namespace rpc
} // namespace crushed

#endif //__RPC_CONTROLLER_HPP
