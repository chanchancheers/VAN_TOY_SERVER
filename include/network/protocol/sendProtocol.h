//
// Created by 신은찬 on 5/19/26.
//

#ifndef SOCKET_SERVER_V2_SENDPROTOCOL_H
#define SOCKET_SERVER_V2_SENDPROTOCOL_H
#include <cstdint>
#include <vector>

struct VANPacket {
    uint8_t type;
    uint8_t* data;
    uint16_t length;
};

class VANProtocol {
    uint8_t magic[2] = {0x50, 0x53};
    uint16_t length;
    uint8_t type;
    uint8_t* data;
    uint16_t MAX_LENGTH = 4096;

public :
    std::vector<uint8_t> serialize();
    VANPacket deserialize(uint8_t* data);
};

#endif //SOCKET_SERVER_V2_SENDPROTOCOL_H