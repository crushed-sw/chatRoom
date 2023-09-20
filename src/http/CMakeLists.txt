aux_source_directory(. SRC_LIST)

add_library(tinyhttp ${SRC_LIST})

target_link_libraries(tinyhttp protobuf cryptopp tinynet tinyrpc)

