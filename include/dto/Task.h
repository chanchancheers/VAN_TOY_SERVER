//
// Created by 신은찬 on 6/3/26.
//

#ifndef SOCKET_SERVER_V2_TASK_H
#define SOCKET_SERVER_V2_TASK_H
#include "../network/protocol/VANProtocol.h"

class Task {
    intptr_t sockfd;
    VANProtocol protocol;
    bool success;

public :
    void setSockfd(intptr_t);
    intptr_t getSockfd() { return sockfd; }

    void setVANProtocol(VANProtocol);
    VANProtocol getVANProtocol () { return protocol; }

    void setSuccess(bool success) { this->success = success; }
    bool isSuccess() { return success; }
};

#endif //SOCKET_SERVER_V2_TASK_H