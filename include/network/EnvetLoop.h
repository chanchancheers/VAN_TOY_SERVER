//
// Created by 신은찬 on 5/20/26.
//

#ifndef SOCKET_SERVER_V2_ENVETLOOP_H
#define SOCKET_SERVER_V2_ENVETLOOP_H
#include <cstdio>
#include <cstdlib>
#include <sys/event.h>
#include "Session.h"
#include "../util/Buffer.h"

class EventLoop {
    int kq;
    EventLoop();
    std::vector<struct kevent> chlist;
    unsigned int MAX_EVENT = 1000;
    std::vector<struct kevent> evlist;
    int pipefd[2];
    Buffer write_buffer;
    Buffer read_buffer;

public :
    EventLoop(const EventLoop&) = delete; // 복사 생성자 삭제
    EventLoop& operator=(const EventLoop&) = delete;

    // 우측값 참조 제한?
    EventLoop(EventLoop&&) = delete;
    EventLoop& operator=(EventLoop&&) = delete;

    static EventLoop& getInstance() {
        static EventLoop eventloop;
        return eventloop;
    }

    void registerSession(Session session);
    void applyPendingChanges();
    int* getPipefd();
    void wakeUp();
    void doLoop();
};

#endif //SOCKET_SERVER_V2_ENVETLOOP_H