//
// Created by 신은찬 on 5/14/26.
//

#ifndef SOCKET_SERVER_V2_ICONNECTION_H
#define SOCKET_SERVER_V2_ICONNECTION_H

#include <cstdint>
#include <vector>

#include "../util/Buffer.h"


class IConnection {
public:
    virtual ~IConnection() = default;
    virtual bool create(const std::string& host, int port) = 0;
    virtual int read(Buffer &buffer, size_t len) = 0;
    virtual int send(const uint8_t* data, size_t len) = 0;
    virtual void close() = 0;

    virtual intptr_t getHandle() const = 0;
};


#endif //SOCKET_SERVER_V2_ICONNECTION_H