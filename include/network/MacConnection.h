//
// Created by 신은찬 on 5/15/26.
//

#ifndef SOCKET_SERVER_V2_MACCONNECTION_H
#define SOCKET_SERVER_V2_MACCONNECTION_H
#include "IConnection.h"
#include <cstdint>
#include "../util/Buffer.h"

class MacConnection : IConnection {
    int sockfd;
public :
    ~MacConnection() = default;
    bool create(const std::string& host, int port);
    int read(Buffer &buffer, size_t len);
    int write(Buffer& buffer);
    void close();
    intptr_t getHandle() const;
};


#endif //SOCKET_SERVER_V2_MACCONNECTION_H