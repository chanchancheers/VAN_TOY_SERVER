#include "../../../include/network/protocol/sendProtocol.h"

#include <vector>

VANPacket VANProtocol::deserialize(uint8_t *data) {

}

std::vector<uint8_t> VANProtocol::serialize() {
    std::vector<uint8_t> serialized_data;
    //1. start
    serialized_data.push_back(magic[0]);
    serialized_data.push_back(magic[1]);
    //2. length
    uint16_t length = htons(this->length); //16bit 타입
    uint8_t* converted_length = reinterpret_cast<uint8_t*>(&length); //16bit타입의 포인터를 8비트포인터로 바꿈
    serialized_data.push_back(converted_length[0]);
    serialized_data.push_back(converted_length[1]);

    //3. type
    serialized_data.push_back(type);

    //4. Payload
    for (int i = 0; i < this->length; i++) {
        serialized_data.push_back(data[i]);
    }
    return serialized_data;

}
