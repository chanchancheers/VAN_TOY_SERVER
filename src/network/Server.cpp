//
// Created by 신은찬 on 5/20/26.
//

#include "../../include/network/Server.h"

#include <unistd.h>

#include "../../include/network/EnvetLoop.h"

Server::Server() : event_loop(EventLoop::getInstance()){

}

void Server::wakeEventLoopUp() {
    event_loop.wakeUp();
}


void Server::close(intptr_t sockfd) {

}

void Server::dispatchEvents() {
    int events_size;
    std::vector<struct kevent> evlist = event_loop.doLoop(events_size);

    for (int i = 0; i < events_size; i++) {
        struct kevent& ev = evlist[i];
        // wakeUp Call
        int wakeUpReadFd = event_loop.getPipefd()[0];
        if (ev.ident == wakeUpReadFd) {
            // while (read(wakeUpReadFd, &read_buffer, read_buffer.size()) > 0);
            while (read(wakeUpReadFd, (event_loop.getReadBuffer()).data(), event_loop.getReadBuffer().size()) > 0);
            event_loop.getReadBuffer().clear();
            continue;
        }

        intptr_t target_sockfd = (intptr_t) ev.ident; // target socket fd
        // close일 경우
        if (ev.filter == EVFILT_READ && ev.flags & EV_EOF) {
            close(target_sockfd);
            continue;
        }

        handleEvent(target_sockfd);
    }
}

/**
 * Worker에게 sockfd를 넘겨주고 이벤트 처리 시작
 * @param sockfd
 */
void Server::handleEvent(intptr_t sockfd) {

}