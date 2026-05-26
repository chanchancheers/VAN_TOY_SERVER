#ifndef SOCKET_SERVER_V2_SERVER_H
#define SOCKET_SERVER_V2_SERVER_H

#include <unordered_map>
#include <sys/event.h>

#include "EventLoop.h"
#include "Session.h"

class Server {
    std::unordered_map<int, std::shared_ptr<Session>> sessions;
    EventLoop& event_loop;
    Server();
public:
    void accept();
    void dispatchEvents();
    void handleEvent(intptr_t sockfd);
    static Server& getInstance() {
        static Server server;
        return server;
    }
    void wakeEventLoopUp();
    void close(intptr_t sockfd);
};


#endif //SOCKET_SERVER_V2_SERVER_H