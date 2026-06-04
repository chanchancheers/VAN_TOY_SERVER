#include "../../../include/network/socket/MacSocket.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <fcntl.h>

MacSocket::MacSocket() {
    read_buffer = Buffer();
    write_buffer = Buffer();
}

bool MacSocket::create(const std::string& host, int port) {
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

int MacSocket::read(std::size_t len) {
    ::read(sockfd, read_buffer.data(), len);
}

int MacSocket::msgPeek() {
    char c;
    return ::recv(sockfd, &c, 1, MSG_PEEK);
}

//
int MacSocket::send(const uint8_t* data, std::size_t len) {
    ::send(sockfd, data, len, MSG_NOSIGNAL);
}

void MacSocket::close() {
    if (sockfd >= 0) {
        ::close(sockfd);
        sockfd = -1;
    }
}

intptr_t MacSocket::getHandle() const {
    return (intptr_t) sockfd;
}

void MacSocket::setHandle(intptr_t sockfd) {
    this->sockfd = sockfd;
}


