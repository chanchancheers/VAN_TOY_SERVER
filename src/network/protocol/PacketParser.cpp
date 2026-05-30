//
// Created by 신은찬 on 5/25/26.
//

#include "../../../include/network/protocol/PacketParser.h"
#include "../../../include/util/Buffer.h"


void PacketParser::findPacketStart(Buffer& buffer, ParsingResult &result) {
    const uint8_t* p = buffer.peek();
    size_t pos = 0;

    //STX PARSING POSSIBLE
    while (pos + VANProtocol::STX_LENGTH - 1 < buffer.readableBytes()) {
        int i = 0;
        for (i = 0; i < VANProtocol::STX_LENGTH; i++) {
            if (p[pos + i] != VANProtocol::STX[i]) break;
        }
        if (i == VANProtocol::STX_LENGTH) {
            result.state = FOUND;
            result.stx_pos = pos;
            result.consumable_bytes = pos - 1;
            return;
        }
        pos++;
    }

    // PARTIAL PROBABILITY CHECK
    int partial_stx_start = detectPartialPacket(p + pos, VANProtocol::STX, VANProtocol::STX_LENGTH) + pos;

    if (partial_stx_start > -1) {
        result.state = WAITING;
        result.consumable_bytes = partial_stx_start;
    } else {
        result.state = NOT_FOUND;
        result.consumable_bytes = partial_stx_start + 1;
    }
}


/**
 *
 * @param p buffer 문자열
 * @param size 비교할 buffer 문자열의 크기
 * @param arr 비교 기준점이 될 문자열 arr(STX, ETX 등)
 * @param start 시작 pos
 * @param matched 일치한 문자열 개수
 * @return 일치 문자열 시작 위치 / 일치하지 않으면 -1
 */
template <size_t N>
int PacketParser::detectPartialPacket(const uint8_t* p, const uint8_t (&arr)[N], unsigned int size, unsigned int start, unsigned int matched) {
    if (start + matched >= size)
        return matched > 0 ? start : -1;

    // if (matched >= VANProtocol::STX_LENGTH)
    if (matched >= std::size(arr))
        return start;

    if (p[start + matched] != arr[matched]) {
        return detectPartialPacket(p, arr, size, ++start, 0);
    }
    return detectPartialPacket(p, arr, size, start, ++matched);
}

int PacketParser::parseLength(Buffer &buffer, unsigned int pos) {
    const uint8_t* p = buffer.peek() + pos;
    return p[pos] << 8 | p[pos + 1];
}

bool PacketParser::findPacketEnd(Buffer& buffer, unsigned int body_start, unsigned int length) {
    const uint8_t* p = buffer.peek() + body_start + length;
    return p[0] == 0x50 && p[1] == 0x45;
}



std::optional<VANProtocol> PacketParser::parse(Buffer& buffer) {
    unsigned int packet_start;
    unsigned int length_start;
    unsigned int body_start;
    if ((packet_start = findPacketStart(buffer)) != -1) {
        length_start = packet_start + VANProtocol::STX_LENGTH;
    } else {
        return std::nullopt;
    }
    unsigned int length = parseLength(buffer, length_start);
    body_start = length_start + VANProtocol::LEN_LENGTH;


    if (findPacketEnd(buffer, body_start, length)) {
        VANProtocol packet;
        packet.setLength(length);
        packet.setData(std::vector<uint8_t>(buffer.peek() + packet_start,
            buffer.peek() + packet_start + length + VANProtocol::ALL_LENGTH));
        return packet;
    } else {
        return std::nullopt;
    }

}