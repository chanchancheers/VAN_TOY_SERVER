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