set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/normalserver)

aux_source_directory(. SRC_LIST)
aux_source_directory(./controller/src CONTROLLER_SRC_LIST)
aux_source_directory(./entity/src ENTITY_SRC_LIST)
aux_source_directory(./service/src SERVICE_SRC_LIST)
aux_source_directory(./util/src UTIL_SRC_LIST)
aux_source_directory(./websocket/src WEBSOCKET_SRC_LIST)

add_executable(server ${SRC_LIST} ${CONTROLLER_SRC_LIST} ${ENTITY_SRC_LIST} ${SERVICE_SRC_LIST} ${UTIL_SRC_LIST} ${WEBSOCKET_SRC_LIST})

target_link_libraries(server tinyhttp protobuf)
