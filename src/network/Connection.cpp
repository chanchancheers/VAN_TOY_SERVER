//
// Created by 신은찬 on 6/2/26.
//

#include "../../include/network/Connection.h"

#include "../../include/network/Factory/SocketFactory.h"

/**
 *
 * 클라이언트는 이쯤 해두자.
 *
 */
Connection::Connection() {
    socket_wrapper = SocketFactory::create();
}

bool Connection::create(const std::string &host, unsigned int port) {
    if (socket_wrapper->create(host, port)) {
        perror("socket connect failed\n");
        exit(EXIT_FAILURE);
    }
}

void Connection::readData(const std::string& str) {
    readData(reinterpret_cast<const uint8_t*>(str.data()), str.size());
}
void Connection::readData(const uint8_t* data, std::size_t len) {

}