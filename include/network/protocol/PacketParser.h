//
// Created by 신은찬 on 5/25/26.
//

#ifndef SOCKET_SERVER_V2_PACKETPARSER_H
#define SOCKET_SERVER_V2_PACKETPARSER_H

#include <cstdint>
#include <optional>
#include "VANProtocol.h"
#include "../../util/Buffer.h"

class PacketParser {
    enum ParserState {
        NOT_FOUND,
        FOUND,
        WAITING,
    };
    struct ParsingResult {
        ParserState state;
        int consumable_bytes; // negatable
        size_t stx_pos;
        size_t length;
        size_t etx_pos;
    };
    ParserState state;
    int parseLength(Buffer& buffer, unsigned int pos);
    int parseType(uint8_t *data);


    ParsingResult findPacketStart(Buffer &buffer);
    bool findPacketEnd(Buffer &buffer, unsigned int body_start, unsigned int length);

    template <size_t N>
    int detectPartialPacket(const uint8_t* p, const uint8_t (&arr)[N], unsigned int size, unsigned int start = 0, unsigned int matched = 0);

public :
    std::optional<VANProtocol> parse(Buffer& buffer);
};

#endif //SOCKET_SERVER_V2_PACKETPARSER_H