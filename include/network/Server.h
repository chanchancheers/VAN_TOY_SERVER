#ifndef SOCKET_SERVER_V2_SERVER_H
#define SOCKET_SERVER_V2_SERVER_H

#include <unordered_map>
#include <sys/event.h>
#include "Session.h"

class Server {
    std::unordered_map<int, std::shared_ptr<Session>> sessions;
    int kq;
public:
    Server() {
        if ((kq = kqueue()) == -1) {
            perror("kqueue");
            exit(EXIT_FAILURE);
        }
    }
    void accept();
};


#endif //SOCKET_SERVER_V2_SERVER_H