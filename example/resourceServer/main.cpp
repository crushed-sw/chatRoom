#include "../../include/rpc/RpcProvider.hpp"
#include "../../include/net/ServerApplication.hpp"
#include "../../include/net/Log.hpp"

#include "include/resourceService.hpp"

int main(int argc, char** argv) {
    crushed::net::ServerApplication::init(argc, argv);

    crushed::rpc::RpcProvider provider;
    provider.notifyService(new ResourceService());
    provider.run();
}
