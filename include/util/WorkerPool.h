//
// Created by 신은찬 on 6/3/26.
//

#ifndef SOCKET_SERVER_V2_WORKERPOOL_H
#define SOCKET_SERVER_V2_WORKERPOOL_H
#include <queue>
#include <thread>
#include "../dto/Task.h"

class WorkerPool {
    WorkerPool(size_t = 10);
    void doWorkerLoop();
    std::vector<std::thread> workers;
    std::queue<Task> jobQueue;
    std::queue<Task> resultQueue;
    Task processTask(Task);


public:
    WorkerPool(const WorkerPool&) = delete;
    WorkerPool& operator=(const WorkerPool&) = delete;

    WorkerPool(WorkerPool&&) = delete;
    WorkerPool& operator=(const WorkerPool&&) = delete;

    static WorkerPool& getInstance(size_t n = 10) {
        static WorkerPool worker_pool(n);
        return worker_pool;
    }


};

#endif //SOCKET_SERVER_V2_WORKERPOOL_H