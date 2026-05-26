//
// Created by 신은찬 on 5/25/26.
//

#ifndef SOCKET_SERVER_V2_VANPROTOCOL_H
#define SOCKET_SERVER_V2_VANPROTOCOL_H
#include <string>
#include <vector>

class VANProtocol {
    std::vector<uint8_t> data;
    int len = 0;
    static uint8_t STX[2];
    static uint8_t ETX[2];

public:
    VANProtocol();
    VANProtocol(const std::string& data);
    VANProtocol(const uint8_t* data, std::size_t len);
    void set(const std::string& data);
    void set(const uint8_t* data, std::size_t len);

};

#endif //SOCKET_SERVER_V2_VANPROTOCOL_H