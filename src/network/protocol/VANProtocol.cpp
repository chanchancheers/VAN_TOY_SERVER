//
// Created by 신은찬 on 5/26/26.
//

#include "../../../include/network/protocol/VANProtocol.h"

const uint8_t VANProtocol::STX[STX_LENGTH] = {0x50, 0x53};
const uint8_t VANProtocol::ETX[ETX_LENGTH] = {0x50, 0x45};

VANProtocol::VANProtocol(const uint8_t* data, std::size_t len) {
    setWithPayload(data, len);
}

VANProtocol::VANProtocol(const std::string& payload) :
    VANProtocol(reinterpret_cast<const uint8_t*>(payload.data()), payload.size()) {}

VANProtocol::VANProtocol(const VANProtocol &protocol) {
    this->len = protocol.len;
    this->data = std::vector<uint8_t>(protocol.data);
}

void VANProtocol::setLength(unsigned int len) {
    this->len = len;
}

void VANProtocol::setData(const uint8_t *p, unsigned int len) {
    setData(std::vector<uint8_t>(p, p + len));
}

void VANProtocol::setData(const std::vector<uint8_t>& data) {
    this->data = data; // std::vector는 기본적으로 값 복사
}


void VANProtocol::setWithPayload(const uint8_t *payload, std::size_t len) {
    this->data.resize(len + std::size(STX) + LEN_LENGTH + std::size(ETX));

    uint8_t* p = this->data.data();
    for (int i = 0; i < std::size(STX); i++) *p++ = STX[i];
    for (int i = LEN_LENGTH - 1; i > -1; i--) {
        *p++ =  len >> (8 * i) & 0xFF;
    }
    for (int i = 0; i < len; i++) *p++ = payload[i];
    for (int i = 0; i < std::size(ETX); i++) *p++ = ETX[i];

    this->len = len;
}

void VANProtocol::setWithPayload(const std::string& data) {
    this->setWithPayload(reinterpret_cast<const uint8_t*>(data.data()), data.size());
}