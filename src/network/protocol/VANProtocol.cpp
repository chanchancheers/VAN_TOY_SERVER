//
// Created by 신은찬 on 5/26/26.
//

#include "../../../include/network/protocol/VANProtocol.h"

const uint8_t VANProtocol::STX[2] = {0x50, 0x53};
const uint8_t VANProtocol::ETX[2] = {0x50, 0x45};

VANProtocol::VANProtocol(const uint8_t* data, std::size_t len) {
    set(data, len);
}

VANProtocol::VANProtocol(const std::string& data) :
    VANProtocol(reinterpret_cast<const uint8_t*>(data.data()), data.size()) {}

void VANProtocol::set(const uint8_t *data, std::size_t len) {
    this->data.resize(len + std::size(STX) + std::size(ETX));

    uint8_t* p = this->data.data();
    for (int i = 0; i < std::size(STX); i++) *p++ = STX[i];
    for (int i = 0; i < len; i++) *p++ = data[i];
    for (int i = 0; i < std::size(ETX); i++) *p++ = ETX[i];

    this->len = len;
}

void VANProtocol::set(const std::string& data) {
    this->set(reinterpret_cast<const uint8_t*>(data.data()), data.size());
}