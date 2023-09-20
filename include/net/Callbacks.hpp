#ifndef __CALL_BACKS_HPP
#define __CALL_BACKS_HPP

#include "Buffer.hpp"
#include "Timer.hpp"

#include <functional>
#include <memory>

namespace crushed {
namespace net {

class TcpConnection;
class Connector;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectorPtr = std::shared_ptr<Connector>;

using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;

using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*, Timer)>;

} // namespace net
} // namespace crushed

#endif //__CALL_BACKS_HPP
