//
// Created by 신은찬 on 6/2/26.
//

#ifndef SOCKET_SERVER_V2_CONNECTION_H
#define SOCKET_SERVER_V2_CONNECTION_H
#include <string>
#include <memory>

#include "../socket/ISocket.h"

class Connection {
    std::unique_ptr<ISocket> socket_wrapper;

    Connection();
    ~Connection();

    bool create(const std::string& host, unsigned int port);
    void close();

    // TODO read write : 간단한 콘솔 출력 정도
    void readData(const std::string&);
    void readData(const uint8_t*, size_t);
    void writeData();
};


#endif //SOCKET_SERVER_V2_CONNECTION_H