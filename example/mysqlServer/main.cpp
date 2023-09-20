#include "../../include/rpc/RpcProvider.hpp"
#include "../../include/net/ServerApplication.hpp"
#include "../../include/net/Log.hpp"

#include "include/chatMessageService.hpp"
#include "include/roomsService.hpp"
#include "include/userService.hpp"

int main(int argc, char** argv) {
    crushed::net::ServerApplication::init(argc, argv);

    crushed::rpc::RpcProvider provider;
    provider.notifyService(new ChatMessageService());
    provider.notifyService(new RoomsService());
    provider.notifyService(new UserService());
    provider.run();
}
