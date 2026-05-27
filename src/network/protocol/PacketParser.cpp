//
// Created by 신은찬 on 5/25/26.
//

#include "../../../include/network/protocol/PacketParser.h"
#include "../../../include/util/Buffer.h"

/**
 * 패킷의 시작점을 탐색
 * @param buffer
 * @return Packet을 찾았을 경우 STX 위치를 반환 / 없을 경우 -1
 */
unsigned int PacketParser::findPacketStart(Buffer &buffer) {
    const uint8_t* p = buffer.peek();
    size_t pos = 0;
    while (pos + 1 < buffer.readableBytes()) {
        if (p[pos] == 0x50 && p[pos+1] == 0x53) {
            buffer.consumeWithExtPos(pos, pos);
            return pos;
        }
        pos++;
    }
    if (p[pos] == 0x50) buffer.consume(pos);
    else buffer.consume(pos + 1);
    return -1;
}

unsigned int PacketParser::parseLength(Buffer &buffer, unsigned int pos) {
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