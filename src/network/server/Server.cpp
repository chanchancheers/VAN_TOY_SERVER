//
// Created by 신은찬 on 5/20/26.
//

#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include "../../../include/network/server/Server.h"
#include "../../../include/network/server/EventLoop.h"
#include "../../../include/network/server/WorkerPool.h"
#include "../../../include/dto/Task.h"

Server::Server() : event_loop(EventLoop::getInstance()){
    // register a listening Event
    LISTEN_FD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(LISTEN_FD, (sockaddr*)& addr, sizeof(addr));
    listen(LISTEN_FD, SOMAXCONN);
    event_loop.registerReadEvent(LISTEN_FD);
}

void Server::wakeEventLoopUp() {
    event_loop.wakeUp();
}


void Server::close(intptr_t sockfd) {

}
void Server::run() {
    while (getServerState() == ServerState::RUNNING) {
        dispatchEvents();
    }
}


void Server::dispatchEvents() {
    int events_size;
    int wakeUpReadFd = event_loop.getPipefd()[0];

    std::vector<struct kevent> evlist = event_loop.doLoop(events_size);
    for (int i = 0; i < events_size; i++) {
        struct kevent& ev = evlist[i];
        // wakeUp Call
        if (ev.ident == wakeUpReadFd) {
            while (::read(wakeUpReadFd, (event_loop.getReadBuffer()).data(), event_loop.getReadBuffer().size()) > 0);
            event_loop.getReadBuffer().clear();
            continue;
        }

        intptr_t target_sockfd = (intptr_t) ev.ident; // target socket fd
        // close일 경우
        if (ev.filter == EVFILT_READ && ev.flags & EV_EOF) {
            close(target_sockfd);
            continue;
        }
        if (target_sockfd == LISTEN_FD && ev.filter == EVFILT_READ ) {
            registerSession();
        }
        handleEvent(target_sockfd);
    }
}

void Server::registerSession() {
    intptr_t sockfd = accept();
    if (sockfd > -1) {
        auto session = std::make_shared<Session>(sockfd);
        sessions.emplace(sockfd, session);
    }
}

intptr_t Server::accept() {
    sockaddr_in client_addr{};
    socklen_t client_addr_size = sizeof(client_addr);
    return ::accept(LISTEN_FD,(sockaddr*)& client_addr, &client_addr_size);
}


/**
 * Worker에게 sockfd를 넘겨주고 이벤트 처리 시작
 * @param sockfd
 */
void Server::handleEvent(intptr_t sockfd) {

}