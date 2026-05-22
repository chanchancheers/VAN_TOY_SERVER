//
// Created by 신은찬 on 5/18/26.
//
#include "../../include/network/Session.h"

std::string Session::handleRead() {
    std::string returned_data;
    int read_byte = read();
    // returned_data = reinterpret_cast<std::string>
    for (int i = 0; i < read_byte; i++) {
        returned_data.push_back(*(read_buffer.peek() + i));
    }
    return returned_data;
}

void Session::handleWrite(std::string client_data) {
    int write_byte = write(reinterpret_cast<const uint8_t*>(client_data.data()), client_data.size());
    // abort(); 또는 whole retry;
    int sent_byte = flush();
    if (client_data.size() != sent_byte) {
        // abort(); 또는 whole retry;
    }
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

int Session::write(const uint8_t* data, size_t len) {
    write_buffer.append(data, len);
    //TODO isWriting 같은 상태처리 필요
    return len;
}

int Session::flush() {
    int n = 0;
    while (write_buffer.readableBytes() > 0) {
        int sent = conn->send(write_buffer.peek(), write_buffer.readableBytes());
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

intptr_t Session::getSockfd() {
    return conn->getHandle();
}

bool Session::checkConeectionAlive() {
    return conn->msgPeek() > 0;
}

