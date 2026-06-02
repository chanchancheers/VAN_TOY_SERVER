//
// Created by 신은찬 on 6/2/26.
//
#include "../../../include/network/Factory/SocketFactory.h"
#include "../../../include/network/MacSocket.h"


std::unique_ptr<ISocket> SocketFactory::create() {
    #ifdef _WIND32

    #else
        return std::make_unique<MacSocket>();
    #endif
}
