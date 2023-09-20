#include "../include/roomService.hpp"

RoomService::RoomService()
        : ip_(crushed::net::ServerApplication::getConfig().getValue("mysql_server_ip"))
        , port_(std::atoi(crushed::net::ServerApplication::getConfig().getValue("mysql_server_port").c_str())) {}

RoomService::~RoomService() {}

Rooms RoomService::query(int roomid) {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel(ip_, port_));
    crushed::rpc::RpcController controller;

    crushed::RoomQueryRequest request;
    crushed::RoomQueryResponse response;

    request.set_roomid(roomid);

    stub.queryRoom(&controller, &request, &response, nullptr);

    Rooms room;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            crushed::Rooms rpcRoom = response.rooms();
            RpcEntity::rpcToEntity(&rpcRoom, room);
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return room;
}

Rooms RoomService::query(const std::string& roomname, int userid) {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomQueryLastRequest request;
    crushed::RoomQueryLastResponse response;

    request.set_roomname(roomname);
    request.set_userid(userid);

    stub.queryLastRoom(&controller, &request, &response, nullptr);

    Rooms room;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            crushed::Rooms rpcRoom = response.rooms();
            RpcEntity::rpcToEntity(&rpcRoom, room);
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return room;
}

void RoomService::insert(const Rooms& rooms) {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomInsertRequest request;
    crushed::RoomInsertResponse response;

    crushed::Rooms* rpcRooms = request.mutable_rooms();
    RpcEntity::entityToRpc(rooms, rpcRooms);

    stub.insertRoom(&controller, &request, &response, nullptr);

    if(!controller.Failed()) {
        if(response.result().code() != 200) {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }
}

void RoomService::remove(int roomid) {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomRemoveRequest request;
    crushed::RoomRemoveResponse response;

    request.set_roomid(roomid);

    stub.removeRoom(&controller, &request, &response, nullptr);

    if(!controller.Failed()) {
        if(response.result().code() != 200) {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }
}

std::vector<Rooms> RoomService::queryAll() {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomQueryAllRequest request;
    crushed::RoomQueryAllResponse response;

    stub.queryAllRoom(&controller, &request, &response, nullptr);

    std::vector<Rooms> vec;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            int size = response.rooms_size();
            for(int i = 0; i != size; ++i) {
                crushed::Rooms rpcRoom = response.rooms(i);
                Rooms room;
                RpcEntity::rpcToEntity(&rpcRoom, room);
                vec.push_back(room);
            }
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return vec;
}

RoomUser RoomService::queryByName(int roomid) {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomQueryByNameRequest request;
    crushed::RoomQueryByNameResponse response;

    request.set_roomid(roomid);

    stub.queryByName(&controller, &request, &response, nullptr);

    RoomUser room;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            crushed::RoomUser rpcRoom = response.roomuser();
            RpcEntity::rpcToEntity(&rpcRoom, room);
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return room;
}

std::vector<RoomUser> RoomService::queryAllByName() {
    crushed::RoomMappingService_Stub stub(new crushed::rpc::RpcChannel("127.0.0.1", 9997));
    crushed::rpc::RpcController controller;

    crushed::RoomQueryAllByNameRequest request;
    crushed::RoomQueryAllByNameResponse response;

    stub.queryAllByName(&controller, &request, &response, nullptr);

    std::vector<RoomUser> vec;
    if(!controller.Failed()) {
        if(response.result().code() == 200) {
            int size = response.roomuser_size();
            for(int i = 0; i != size; ++i) {
                crushed::RoomUser rpcRoom = response.roomuser(i);
                RoomUser room;
                RpcEntity::rpcToEntity(&rpcRoom, room);
                vec.push_back(room);
            }
        } else {
            LogError << response.result().msg() << LogEnd;
        }
    } else {
        LogError << "mysqlServer is down" << LogEnd;
    }

    return vec;
}
