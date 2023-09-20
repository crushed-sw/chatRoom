#!/bin/bash

set -e

if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

cd build
cmake ..
make
cd ..

echo "
# 服务器端口号
server_port = 9999
# 服务器线程数量
server_threadnum = 4

# 静态资源服务器ip
resource_ip = 127.0.0.1
# 静态资源服务器端口号
resource_port = 9998
 
# mysql服务器ip
mysql_server_ip = 127.0.0.1
# mysql服务器端口号
mysql_server_port = 9997
" > `pwd`/bin/normalserver/server.conf

echo "
# 数据库URL和数据库名称
sql_url = tcp://localhost:3306/webserver
# 数据库用户名
sql_user = root
# 数据库密码
sql_password = zk200111
# 数据库连接池数量
sql_poolsize = 4

# 当前服务器监听ip
rpc_server_ip = 127.0.0.1
# 当前服务器端口号
rpc_server_port = 9997
" > `pwd`/bin/mysqlserver/mysqlserver.conf

echo "
# 静态资源目录
resource = /home/crushed/c/webwebserver/rpcwebserver/example/resource

# 当前服务器将听ip
rpc_server_ip = 127.0.0.1
# 当前服务器端口号
rpc_server_port = 9998
" > `pwd`/bin/resourceserver/resourceserver.conf
