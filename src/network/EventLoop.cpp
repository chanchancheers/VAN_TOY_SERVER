#include <unistd.h>
#include <sys/event.h>
#include <sys/fcntl.h>

#include "../../include/network/EventLoop.h"
#include "../../include/util/Buffer.h"


EventLoop::EventLoop() : evlist(MAX_EVENT) {
    if ((kq = kqueue()) == -1) {
        perror("kqueue");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    struct kevent kev;
    EV_SET(&kev, pipefd[0], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
    if (kevent(kq,&kev, 1, NULL, 0, NULL) == -1) {
        perror("pipe event not registered.");
        exit(EXIT_FAILURE);
    }
    // 이것만큼은 Non-blocking
    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);
}


/*
while (running) {

    // 1. pending change 반영
    applyPendingChanges();

    // 2. 이벤트 대기
    int nev = kevent(...);

    // 3. 이벤트 처리
    handleEvents();
}

"event loop 깨우기(wakeup)"

메커니즘이 필요하다.

대표적으로:

pipe
EVFILT_USER
eventfd(Linux)
self-pipe trick

등을 사용한다.

예를 들면 kqueue에서는:

event loop thread
while (running) {

    applyPendingChanges();

    kevent(kq, ... NULL); // block
}
다른 thread
enqueueChange(...);

wakeupEventLoop();
*/



void EventLoop::registerSession(Session session) {
    // chlist에 감시할 sockfd를 넣고, READ가 발생하는지 본다. 등록하면서 ADD 및 ENABLE 처리.
    struct kevent kev;
    EV_SET(&kev, session.getSockfd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0,0,0);
    chlist.push_back(kev);
}

void EventLoop::applyPendingChanges() {
    if (kevent(kq, chlist.data(), chlist.size(), evlist.data(), evlist.size(), nullptr) == -1) {
        perror("kevent has error");
        exit(EXIT_FAILURE);
    }
}

void EventLoop::wakeUp() {
    int garbage = 1;
    int n = write(pipefd[1], &garbage, 1);
    if (n == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("write pipe error");
        exit(EXIT_FAILURE);
    }
}

std::vector<struct kevent> EventLoop::doLoop(int& event_size) {
    while (true) {
        //1. 이벤트 발생 체크 후 등록
        applyPendingChanges();
        //2. 현상태로 고정 후 감시 시작
        event_size = kevent(kq,
                            nullptr,
                            0,
                            evlist.data(),
                            evlist.size(),
                            nullptr);
        /*!--  아무 이벤트가 없다면 이 시점에서 대기가 이루어진다   --!*/

        return evlist;
    }
}