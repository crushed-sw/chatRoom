#ifndef __ROOMS_MESSAGE_SERVICE_HPP
#define __ROOMS_MESSAGE_SERVICE_HPP

#include "../entity/include/rooms.hpp"
#include "../entity/include/roomUser.hpp"
#include "../entity/include/rpcEntiry.hpp"

#include "roomsMapping.hpp"
#include "mysql.pb.h"

class RoomsService : public crushed::RoomMappingService {
public:
    void queryRoom(::google::protobuf::RpcController* controller,
                   const ::crushed::RoomQueryRequest* request,
                   ::crushed::RoomQueryResponse* response,
                   ::google::protobuf::Closure* done) override;

    void queryLastRoom(::google::protobuf::RpcController* controller,
                       const ::crushed::RoomQueryLastRequest* request,
                       ::crushed::RoomQueryLastResponse* response,
                       ::google::protobuf::Closure* done) override;

    void insertRoom(::google::protobuf::RpcController* controller,
                    const ::crushed::RoomInsertRequest* request,
                    ::crushed::RoomInsertResponse* response,
                    ::google::protobuf::Closure* done) override;

    void removeRoom(::google::protobuf::RpcController* controller,
                    const ::crushed::RoomRemoveRequest* request,
                    ::crushed::RoomRemoveResponse* response,
                    ::google::protobuf::Closure* done) override;

    void queryAllRoom(::google::protobuf::RpcController* controller,
                      const ::crushed::RoomQueryAllRequest* request,
                      ::crushed::RoomQueryAllResponse* response,
                      ::google::protobuf::Closure* done) override;

    void queryByName(::google::protobuf::RpcController* controller,
                     const ::crushed::RoomQueryByNameRequest* request,
                     ::crushed::RoomQueryByNameResponse* response,
                     ::google::protobuf::Closure* done) override;

    void queryAllByName(::google::protobuf::RpcController* controller,
                       const ::crushed::RoomQueryAllByNameRequest* request,
                       ::crushed::RoomQueryAllByNameResponse* response,
                       ::google::protobuf::Closure* done) override;



private:
    RoomsMapping roomsMapping_;
};

#endif //__ROOMS_MESSAGE_SERVICE_HPP
