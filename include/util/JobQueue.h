//
// Created by 신은찬 on 6/4/26.
//

#ifndef SOCKET_SERVER_V2_JOBQUEUE_H
#define SOCKET_SERVER_V2_JOBQUEUE_H
#include <mutex>
#include <queue>

template <typename T>
class JobQueue {
    std::queue<T> queue;
    std::mutex mutex_;
    std::condition_variable cv;

public:
    void push(T);
    T pop();
};

#endif //SOCKET_SERVER_V2_JOBQUEUE_H