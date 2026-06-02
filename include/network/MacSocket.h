//
// Created by 신은찬 on 5/15/26.
//

#ifndef SOCKET_SERVER_V2_MACSOCKET_H
#define SOCKET_SERVER_V2_MACSOCKET_H
#include "ISocket.h"
#include "../util/Buffer.h"

class MacSocket : public ISocket {
    int sockfd;
public :
    MacSocket();
    ~MacSocket() = default;

    bool create(const std::string& host, int port);
    void close();

    int read(std::size_t len);
    int send(const uint8_t* data, std::size_t len);
    int msgPeek();

    intptr_t getHandle() const;
    void setHandle(intptr_t sockfd);
};


#endif //SOCKET_SERVER_V2_MACSOCKET_H