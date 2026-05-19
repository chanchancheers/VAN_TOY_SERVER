#include "../../deprecated/SocketFactory.h"

#ifdef __APPLE__
    #include "../../include/deprecated/Socket_mac.h"
#else
#include "../../include/network/Socket_win.h"
#endif


std::unique_ptr<ISocket> createSocket() {
    #ifdef __APPLE__
        return std::make_unique<MacSocket>();
    #else
        return nullptr; //TODO 구현 필요
    #endif
}
