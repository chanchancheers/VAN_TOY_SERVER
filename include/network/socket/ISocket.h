//
// Created by 신은찬 on 5/14/26.
//

#ifndef SOCKET_SERVER_V2_ISOCKET_H
#define SOCKET_SERVER_V2_ISOCKET_H

#include <cstdint>
#include <vector>

#include "../../util/Buffer.h"

class ISocket {
public:
    Buffer read_buffer;
    Buffer write_buffer;

    virtual ~ISocket() = default;
    virtual bool create(const std::string& host, int port) = 0;
    virtual void close() = 0;

    virtual int read(std::size_t len) = 0;
    virtual int send(const uint8_t* data, std::size_t len) = 0;
    virtual int msgPeek() = 0;

    virtual intptr_t getHandle() const = 0;
    virtual void setHandle(intptr_t sockfd) = 0;
};


#endif //SOCKET_SERVER_V2_ISOCKET_H