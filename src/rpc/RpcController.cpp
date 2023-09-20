#include "../../include/rpc/RpcController.hpp"

using namespace crushed::rpc;

RpcController::RpcController() : failed_(false), errorMessage_("") {}

void RpcController::Reset() {
    failed_ = false;
    errorMessage_ = "";
}

bool RpcController::Failed() const {
    return failed_;
}

std::string RpcController::ErrorText() const {
    return errorMessage_;
}

void RpcController::SetFailed(const std::string& reason) {
    failed_ = true;
    errorMessage_ = reason;
}

void RpcController::StartCancel() {}

bool RpcController::IsCanceled() const { return false; }

void RpcController::NotifyOnCancel(google::protobuf::Closure* callback) {}
