//
// Created by 신은찬 on 5/18/26.
//
#include "../../include/util/Buffer.h"

int Buffer::append(const uint8_t* data, size_t len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        buffer.push_back(data[i]);
    }
    return i;
}

int Buffer::consume(int n) {
    offset += n;

    if (offset > threshold) {
        buffer.erase(buffer.begin(), buffer.begin() + offset);
        offset = 0;
    }
    return n;
}

int Buffer::size() {
    return buffer.size();
}

const uint8_t* Buffer::peek() const {
    return buffer.data() + offset;
}

size_t Buffer::readableBytes() {
    return buffer.size() - offset;
}

void Buffer::clear() {
    consume(buffer.size());
}