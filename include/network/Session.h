//
// Created by 신은찬 on 5/6/26.
//

#ifndef SOCKET_SERVER_V2_SESSION_H
#define SOCKET_SERVER_V2_SESSION_H

#include <vector>
#include <memory>
#include "../../include/network/IConnection.h"
#include "../../include/util/Buffer.h"

class Session {
    std::shared_ptr<IConnection> conn;

    Buffer read_buffer;
    Buffer write_buffer;

    enum class State {
        //
    };

    State state;

    std::string handleRead();
    void handleWrite(std::string client_data);

    int read();
    int write(const uint8_t* data, std::size_t len);
    int flush();
    bool checkConeectionAlive();

    // bool tryParseMessage(std::vector<uint8_t>& out_message);
    // void dispatchToWorker(const std::vector<uint8_t>& message);

    void close();

public :
    explicit Session(std::shared_ptr<IConnection> conn);
    ~Session();

    intptr_t getSockfd();

    int BUFFER_SIZE = 4096;

    void onReadable();
    void onWritable();
    void onClosed();

    void send(const std::vector<uint8_t>& data);

};

#endif //SOCKET_SERVER_V2_SESSION_H