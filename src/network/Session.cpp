//
// Created by 신은찬 on 5/18/26.
//
#include "../../include/network/Session.h"

void Session::handleRead() {

}

int Session::read() {
    int len = 0;
    uint8_t tmp[BUFFER_SIZE];
    while (true) {
        int n = conn->read(read_buffer, read_buffer.readableBytes());
        if (n > 0) read_buffer.append(tmp, n);
        else if (n == 0) return 0;
        else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            return -1;
        }
        len += n;
    }
    return len;
}

int Session::write() {

}

int Session::flush() {
    int n = 0;
    while (write_buffer.readableBytes() > 0) {
        int sent = conn->write(write_buffer);
        if (sent > 0) {
            write_buffer.consume(sent);
            n += sent;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return 0;
            }
            return -1;
        }
    }
    return n;
}