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

/**
 * 버퍼를 소비. offset의 상한선을 초과하면 버퍼를 비우고 offset을 초기화시킨다.
 * @param n
 * @return erase가 발생했으면 1, 발생하지 않았으면 0을 리턴
 */
int Buffer::consume(int n) {
    offset += n;
    bool is_erased;
    if (is_erased = (offset > threshold)) {
        buffer.erase(buffer.begin(), buffer.begin() + offset);
        offset = 0;
    }
    return is_erased;
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

void Buffer::consumeWithExtPos(int n, std::size_t& pos) {
    if (consume(n)) {
        pos -= n;
    }
}