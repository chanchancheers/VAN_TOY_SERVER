//
// Created by 신은찬 on 5/25/26.
//

#ifndef SOCKET_SERVER_V2_PACKETPARSER_H
#define SOCKET_SERVER_V2_PACKETPARSER_H

#include <cstdint>
#include <optional>

class Buffer;

class PacketParser {
public :
    enum ParserState {
    NOT_FOUND,
    FOUND,
    WAITING,
    ABORT,
    COMPLETE,
    };
    struct ParsingResult {
        ParserState state;
        int consumable_bytes; // negatable
        size_t stx_pos;
        size_t length;
        size_t etx_pos;
    };
    ParsingResult parse(Buffer& buffer);
private:
    int parseType(uint8_t *data);

    void findPacketStart(Buffer &buffer, ParsingResult &result);
    void findPacketLength(Buffer &buffer, ParsingResult &result);
    void findPacketEnd(Buffer &buffer, ParsingResult &result);
    bool proceedToNext(ParsingResult &result);

    template <size_t N>
    int detectPartialPacket(const uint8_t* p, const uint8_t (&arr)[N], unsigned int size, unsigned int start = 0, unsigned int matched = 0);

};

#endif //SOCKET_SERVER_V2_PACKETPARSER_H