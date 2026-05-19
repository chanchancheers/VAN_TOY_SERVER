//
// Created by 신은찬 on 5/18/26.
//

#ifndef SOCKET_SERVER_V2_BUFFER_H
#define SOCKET_SERVER_V2_BUFFER_H

#include <vector>
#include <memory>

class Buffer {
    std::vector<uint8_t> buffer;
    int offset = 0;
    int threshold = 1024 * 8;
public :
    int append(uint8_t* data, int len);
    int consume(int n);

    const uint8_t* peek() const;
    int readableBytes();
    int size();
    uint8_t* data() { return buffer.data(); }


};


#endif //SOCKET_SERVER_V2_BUFFER_H