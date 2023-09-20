aux_source_directory(. SRC_LIST)

add_library(tinymysql ${SRC_LIST})

target_link_libraries(tinymysql mysqlcppconn)

