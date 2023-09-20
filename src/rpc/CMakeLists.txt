aux_source_directory(. SRC_LIST)

add_library(tinyrpc ${SRC_LIST})

target_link_libraries(tinyrpc tinynet)
