//
// Created by 신은찬 on 6/2/26.
//

#ifndef SOCKET_SERVER_V2_SOCKETFACTORY_H
#define SOCKET_SERVER_V2_SOCKETFACTORY_H

#include <memory>

#include "../ISocket.h"

class SocketFactory {
public :
    static std::unique_ptr<ISocket> create();
};

#endif //SOCKET_SERVER_V2_SOCKETFACTORY_H