#ifndef SOCKET_SERVER_V2_SERVER_H
#define SOCKET_SERVER_V2_SERVER_H

#include <unordered_map>
#include <sys/event.h>
#include "Session.h"

class Server {
    std::unordered_map<int, std::shared_ptr<Session>> sessions;
public:
    void accept();
};


#endif //SOCKET_SERVER_V2_SERVER_H