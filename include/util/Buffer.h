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
    int append(const uint8_t* data, std::size_t len);
    int consume(int n);

    const uint8_t* peek() const;
    std::size_t readableBytes();
    int size();
    uint8_t* data() { return buffer.data(); }
    void clear();


};


#endif //SOCKET_SERVER_V2_BUFFER_H