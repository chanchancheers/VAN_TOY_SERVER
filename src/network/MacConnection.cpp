#include "../../include/network/MacConnection.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <fcntl.h>

bool MacConnection::create(const std::string& host, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) return false;
    bool connected = ::connect(sockfd, (sockaddr*)&addr, sizeof(addr)) == 0;
    if (connected) {
        int flags = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    }
    return connected;
}

int MacConnection::read(Buffer &buffer, size_t len) {
    ::read(sockfd, buffer.data(), len);
}

//
int MacConnection::write(Buffer &buffer) {
    ::send(sockfd, buffer.peek(), buffer.readableBytes(), MSG_NOSIGNAL);
}

void MacConnection::close() {
    if (sockfd >= 0) {
        ::close(sockfd);
        sockfd = -1;
    }
}

intptr_t MacConnection::getHandle() const {
    return (intptr_t) sockfd;
}



