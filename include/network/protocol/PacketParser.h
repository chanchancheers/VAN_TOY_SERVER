//
// Created by 신은찬 on 5/25/26.
//

#ifndef SOCKET_SERVER_V2_PACKETPARSER_H
#define SOCKET_SERVER_V2_PACKETPARSER_H

#include <cstdint>
#include <optional>
#include "VANProtocol.h"
#include "../../enum/PacketType.h"
#include "../../util/Buffer.h"

class PacketParser {
    enum ParserState {
        WAIT_STX,
        READ_HEAD,
        READ_BODY,
        CHECK_ETX
    };
    bool headerPartiallyDetected = false;
    ParserState state;
    PacketType type;
    uint16_t length;
public :
    std::optional<VANProtocol> parse(Buffer& buffer);
    int findPacketStart(Buffer& buffer);
    int findPacketEnd(Buffer& buffer, int pos);
    int parseLength(uint8_t* data);
    int parseType(uint8_t* data);
};

#endif //SOCKET_SERVER_V2_PACKETPARSER_H