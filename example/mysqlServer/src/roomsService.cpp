#include "../include/roomsService.hpp"

void RoomsService::queryRoom(::google::protobuf::RpcController* controller,
                             const ::crushed::RoomQueryRequest* request,
                             ::crushed::RoomQueryResponse* response,
                             ::google::protobuf::Closure* done) {
    try {
        int roomid = request->roomid();
        Rooms room = roomsMapping_.query(roomid);

        crushed::Rooms* rpcRooms = response->mutable_rooms();
        RpcEntity::entityToRpc(room, rpcRooms);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "queryRoom mysql异常", result);
    }
    done->Run();
}

void RoomsService::queryLastRoom(::google::protobuf::RpcController* controller,
                                 const ::crushed::RoomQueryLastRequest* request,
                                 ::crushed::RoomQueryLastResponse* response,
                                 ::google::protobuf::Closure* done) {
    try {
        int userid = request->userid();
        std::string roomname = request->roomname();
        Rooms room = roomsMapping_.query(roomname, userid);

        crushed::Rooms* rpcRooms = response->mutable_rooms();
        RpcEntity::entityToRpc(room, rpcRooms);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "queryLastRoom mysql异常", result);
    }
    done->Run();
}

void RoomsService::insertRoom(::google::protobuf::RpcController* controller,
                              const ::crushed::RoomInsertRequest* request,
                              ::crushed::RoomInsertResponse* response,
                              ::google::protobuf::Closure* done) {
    try {
        crushed::Rooms rpcRoom = request->rooms();
        Rooms room;
        RpcEntity::rpcToEntity(&rpcRoom, room);

        roomsMapping_.insert(room);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "insertRoom mysql异常", result);
    }
    done->Run();
}

void RoomsService::removeRoom(::google::protobuf::RpcController* controller,
                              const ::crushed::RoomRemoveRequest* request,
                              ::crushed::RoomRemoveResponse* response,
                              ::google::protobuf::Closure* done) {
    try {
        int roomid = request->roomid();

        roomsMapping_.remove(roomid);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "removeRoom mysql异常", result);
    }

    done->Run();
}

void RoomsService::queryAllRoom(::google::protobuf::RpcController* controller,
                                const ::crushed::RoomQueryAllRequest* request,
                                ::crushed::RoomQueryAllResponse* response,
                                ::google::protobuf::Closure* done) {
    try {
        std::vector<Rooms> rooms = roomsMapping_.queryAll();

        for(Rooms room : rooms) {
            crushed::Rooms* rpcRoom = response->add_rooms();
            RpcEntity::entityToRpc(room, rpcRoom);
        }

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "queryALlRoom mysql异常", result);
    }
    done->Run();
}

void RoomsService::queryByName(::google::protobuf::RpcController* controller,
                               const ::crushed::RoomQueryByNameRequest* request,
                               ::crushed::RoomQueryByNameResponse* response,
                               ::google::protobuf::Closure* done) {
    try {
        int roomid = request->roomid();

        RoomUser roomuser = roomsMapping_.queryByName(roomid);

        crushed::RoomUser* rpcRoom = response->mutable_roomuser();
        RpcEntity::entityToRpc(roomuser, rpcRoom);

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "queryByName mysql异常", result);
    }
    done->Run();
}

void RoomsService::queryAllByName(::google::protobuf::RpcController* controller,
                                  const ::crushed::RoomQueryAllByNameRequest* request,
                                  ::crushed::RoomQueryAllByNameResponse* response,
                                  ::google::protobuf::Closure* done) {
    try {
        std::vector<RoomUser> roomusers = roomsMapping_.queryAllByName();

        for(RoomUser roomuser : roomusers) {
            crushed::RoomUser* rpcRoomUser = response->add_roomuser();
            RpcEntity::entityToRpc(roomuser, rpcRoomUser);
        }

        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(200, "OK", result);
    } catch(std::exception e) {
        crushed::MysqlResultCode* result = response->mutable_result();
        RpcEntity::entityToRpc(100, "queryAllByName mysql异常", result);
    }
    done->Run();
}

