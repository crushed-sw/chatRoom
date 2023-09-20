#ifndef __CONNECTOR_HPP
#define __CONNECTOR_HPP

#include "NonCopyable.hpp"
#include "InetAddress.hpp"
#include "Log.hpp"

#include <memory>
#include <functional>

namespace crushed {
namespace net {

class Channel;
class EventLoop;

class Connector : public NonCopyable, public std::enable_shared_from_this<Connector> {
public:
    using NewConnectionCallback = std::function<void(int)>;

    Connector(EventLoop* loop, const InetAddress& address);
    ~Connector();

    void start();
    void restart();
    void stop();

    const InetAddress& getAddress() const;

    void setNewConnectionCallback(const NewConnectionCallback& cb);

private:
    enum State {Disconnected, Connecting, Connected};

    static const int MaxRetryDelay = 30 * 1000;
    static const int InitRetryDelay = 500;

    int removeAndResetChannel();
    void resetChannel();
    void connect();
    void connecting(int sockfd);
    void startInLoop();
    void stopInLoop();
    void retry(int sockfd);

    void handleWrite();
    void handleError();

    EventLoop* loop_;
    InetAddress address_;
    bool connect_;
    State state_;
    std::unique_ptr<Channel> channel_;
    NewConnectionCallback newConnectionCallback_;
    int relayTime_;
};

} // namespace net
} // namespace crushed

#endif //__CONNECTOR_HPP
