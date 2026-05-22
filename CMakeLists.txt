cmake_minimum_required(VERSION 4.0)
project(socket_server_v2)

set(CMAKE_CXX_STANDARD 23)

add_executable(socket_server_v2 main.cpp
        deprecated/Socket_mac.cpp
        deprecated/ISocket.h
        deprecated/SocketFactory.cpp
        deprecated/SocketFactory.h
        deprecated/Socket_mac.h
        deprecated/Socket_win.h
        deprecated/Socket_win.cpp
        include/network/Session.h
        include/network/Server.h
        include/network/IConnection.h
        include/network/MacConnection.h
        src/network/MacConnection.cpp
        src/network/Session.cpp
        include/util/Buffer.h
        src/util/Buffer.cpp
        include/network/protocol/sendProtocol.h
        src/network/protocol/sendProtocol.cpp
        src/network/Server.h.cpp
        include/network/EnvetLoop.h
        src/network/EventLoop.cpp)
