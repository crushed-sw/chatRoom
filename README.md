# webserver

### 依赖
编译需要依赖`mysqlcppconn`库、`cryptopp`库、`protobuf`库
```
sudo apt install libmysqlcppconn-dev
sudo apt install build-essential cmake
sudo apt install protobuf-compiler libprotobuf-dev

wget https://www.cryptopp.com/cryptopp830.zip
unzip cryptopp830.zip
cd cryptopp830
make
sudo make install
```

### 编译
编译源文件
```
./make.sh
```

### 使用
将'include'和`lib`文件夹下的文件移动到相应位置，如：
```
sudo mv include/* /usr/local/include
sudo mv lib/* /usr/local/lib
```

创建数据库：
```mysql
create database webserver;
use webserver;

create table user(userid int primary key, username varchar(50) not null, password varchar(50) not null);
create table rooms(roomid int auto_increment key, roomname varchar(50) not null unique, roomuser int not null, isdelete boolean default false);
create table chat(chatid int auto_increment key, roomid int not null, userid int not null, sendtime varchar(50) not null, message text);
```

在`bin`下相应的服务器文件夹填写相应的配置信息，详看`.conf`文件

运行`mysql`服务器程序
```
./mysqlServer -i mysqlserver.conf
```

运行静态资源服务器程序
```
./resourceServer -i resourceserver.conf
```

运行`server`程序
```
./server -i server.conf
```


