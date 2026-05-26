//
// Created by 신은찬 on 5/18/26.
//
#include "../../include/util/Buffer.h"

int Buffer::append(const uint8_t* data, std::size_t len) {
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

/**
 * @return 읽을 수 있는 버퍼의 배열포인터
 */
const uint8_t* Buffer::peek() const {
    return buffer.data() + offset;
}

std::size_t Buffer::readableBytes() {
    return buffer.size() - offset;
}

void Buffer::clear() {
    consume(buffer.size());
}