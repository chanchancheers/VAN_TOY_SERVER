//
// Created by 신은찬 on 5/25/26.
//

#ifndef SOCKET_SERVER_V2_VANPROTOCOL_H
#define SOCKET_SERVER_V2_VANPROTOCOL_H
#include <string>
#include <vector>

class Buffer;

class VANProtocol {
    std::vector<uint8_t> data;
    unsigned int len = 0;
public:
    static constexpr unsigned int STX_LENGTH = 2;
    static constexpr unsigned int ETX_LENGTH = 2;
    static constexpr unsigned int LEN_LENGTH = 2;
    static constexpr unsigned int ALL_LENGTH = STX_LENGTH + ETX_LENGTH + LEN_LENGTH;

    static const uint8_t STX[STX_LENGTH];
    static const uint8_t ETX[ETX_LENGTH];
    VANProtocol();
    VANProtocol(const std::string& payload);
    VANProtocol(const uint8_t* data, std::size_t len);
    VANProtocol(const VANProtocol& protocol);

    void setLength(unsigned int len);
    void setData(const uint8_t* p, unsigned int len);
    void setData(const std::vector<uint8_t>& data);

    void setWithPayload(const std::string& data);
    void setWithPayload(const uint8_t* payload, std::size_t len);
    void setWithPacket(const uint8_t* raw_data);

    unsigned int getLength() { return len; }
};

#endif //SOCKET_SERVER_V2_VANPROTOCOL_H