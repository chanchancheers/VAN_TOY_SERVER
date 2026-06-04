//
// Created by 신은찬 on 6/4/26.
//

#ifndef SOCKET_SERVER_V2_NOTIFIER_H
#define SOCKET_SERVER_V2_NOTIFIER_H
#include "EventLoop.h"

class Notifier {
public :
    static void wakeUpWriteEvent() {
        EventLoop::getInstance().wakeUpWrite();
    }
};

#endif //SOCKET_SERVER_V2_NOTIFIER_H