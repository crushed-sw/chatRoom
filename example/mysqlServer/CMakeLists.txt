set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/mysqlserver)

aux_source_directory(./src SRC_LIST)
aux_source_directory(./entity/src ENTIRY_SRC_LIST)

add_executable(mysqlServer ./main.cpp ${SRC_LIST} ${ENTIRY_SRC_LIST})

target_link_libraries(mysqlServer tinymysql tinyrpc protobuf)
