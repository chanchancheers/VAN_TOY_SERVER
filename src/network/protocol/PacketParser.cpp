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

void PacketParser::findPacketLength(Buffer& buffer, ParsingResult& result) {
    size_t length_start = result.stx_pos + VANProtocol::STX_LENGTH;

    if (length_start + 1 > buffer.readableBytes()) {
        result.state = WAITING;
        return;
    }

    const uint8_t* p = buffer.peek() + length_start;
    size_t len = 0;
    for (int i = 0; i < VANProtocol::LEN_LENGTH; i++)
        len |= p[i] << (8 * (VANProtocol::LEN_LENGTH - 1 - i));
    if (len <= VANProtocol::LENGTH_LIMIT) {
        result.state = FOUND;
        result.length = len;
        result.etx_pos = length_start + VANProtocol::LEN_LENGTH + len;
    } else {
        result.state = ABORT;
    }
}

void PacketParser::findPacketEnd(Buffer& buffer, ParsingResult& result) {
    if (buffer.readableBytes() < VANProtocol::ALL_LENGTH + result.length) {
        result.state = WAITING;
        return;
    }
    const uint8_t* p = buffer.peek() + result.etx_pos;
    int i;
    for (i = 0; i < VANProtocol::ETX_LENGTH; i++) {
        if (p[i] != VANProtocol::ETX[i]) break;
    }
    if (i == VANProtocol::ETX_LENGTH) {
        result.state = COMPLETE;
    } else {
        result.state = ABORT;
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

PacketParser::ParsingResult PacketParser::parse(Buffer& buffer) {
    ParsingResult result;
    //STX check
    findPacketStart(buffer, result);
    if (!proceedToNext(result)) {
        return result;
    }
    //length check
    findPacketLength(buffer, result);
    if (!proceedToNext(result)) {
        return result;
    }
    findPacketEnd(buffer, result);
    if (proceedToNext(result)) {

    }
    return result;
}

bool PacketParser::proceedToNext(ParsingResult &result) {
    switch (result.state) {
        case FOUND :
        case COMPLETE:
            return true;
        case NOT_FOUND :
            break;
        case WAITING :
            break;
    }
    return false;
}