//
// Created by 신은찬 on 5/6/26.
//

#ifndef SOCKET_SERVER_V2_SESSION_H
#define SOCKET_SERVER_V2_SESSION_H

#include <vector>
#include <memory>
#include "../../include/network/ISocket.h"
#include "../../include/util/Buffer.h"
#include "../../include/network/protocol/PacketParser.h"

class Session {
    std::unique_ptr<ISocket> socket;

    PacketParser packet_parser;

    enum class State {
        ACTIVE,
        CLOSING
    };

    State state;

    void handleRead();
    void handleWrite(std::string client_data);

    int read();
    int write(const uint8_t* data, std::size_t len);
    int flush();
    bool checkConeectionAlive();

    // bool tryParseMessage(std::vector<uint8_t>& out_message);
    // void dispatchToWorker(const std::vector<uint8_t>& message);

    void close();

public :
    explicit Session(intptr_t sockfd);
    ~Session();

    intptr_t getSockfd();

    void onReadable();
    void onWritable();
    void onClosed();

    void send(const std::vector<uint8_t>& data);

};

#endif //SOCKET_SERVER_V2_SESSION_H