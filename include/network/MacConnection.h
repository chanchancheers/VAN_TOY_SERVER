//
// Created by 신은찬 on 5/15/26.
//

#ifndef SOCKET_SERVER_V2_MACCONNECTION_H
#define SOCKET_SERVER_V2_MACCONNECTION_H
#include "IConnection.h"
#include "../util/Buffer.h"

class MacConnection : IConnection {
    int sockfd;
public :
    ~MacConnection() = default;
    bool create(const std::string& host, int port);
    int read(Buffer &buffer, std::size_t len);
    int msgPeek();
    int send(const uint8_t* data, std::size_t len);
    void close();
    intptr_t getHandle() const;
};


#endif //SOCKET_SERVER_V2_MACCONNECTION_H