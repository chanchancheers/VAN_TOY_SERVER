#ifndef SOCKET_SERVER_V2_SERVER_H
#define SOCKET_SERVER_V2_SERVER_H

#include <unordered_map>
#include <sys/event.h>

#include "EventLoop.h"
#include "Session.h"
#include "WorkerPool.h"

class Server {
    std::unordered_map<int, std::shared_ptr<Session>> sessions;
    EventLoop& event_loop;
    WorkerPool& worker_pool;
    intptr_t LISTEN_FD;
    Server();

public:
    enum class ServerState {
        RUNNING,
        CLOSING,
        CLOSED,
    };
    const int PORT  = 40445;
    void run();

    void dispatchEvents();

    void registerSession();
    intptr_t accept();

    void handleEvent(intptr_t sockfd);
    static Server& getInstance() {
        static Server server;
        return server;
    }
    void wakeEventLoopUp();
    void close(intptr_t sockfd);
    ServerState getServerState();
    void setServerState(ServerState);
private :
    ServerState state;
};


#endif //SOCKET_SERVER_V2_SERVER_H