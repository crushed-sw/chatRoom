set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/resourceserver)

aux_source_directory(./src SRC_LIST)

add_executable(resourceServer ./main.cpp ${SRC_LIST})

target_link_libraries(resourceServer tinyrpc protobuf)
