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

int MacConnection::read(Buffer &buffer) {
    int len = 0;
    uint8_t temp[4096]; //TODO hardcoded
    while (true) {
        int n = ::recv(sockfd, temp, sizeof(temp), 0);
        if (n > 0) buffer.append(temp, n);
        else if (n == 0) return 0;
        else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            return -1;
        }
        len += n;
    }
    return len;
}

int MacConnection::write(const uint8_t *buffer, size_t len) {

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



