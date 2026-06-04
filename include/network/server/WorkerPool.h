//
// Created by 신은찬 on 6/3/26.
//

#ifndef SOCKET_SERVER_V2_WORKERPOOL_H
#define SOCKET_SERVER_V2_WORKERPOOL_H
#include <queue>
#include <thread>
#include "../../dto/Task.h"
#include "../../util/JobQueue.h"

class WorkerPool {
    WorkerPool(size_t = 10);
    void doWorkerLoop();
    std::vector<std::thread> workers;
    JobQueue<Task> job_queue;
    JobQueue<Task> result_queue;
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

    void enqueue(Task task) {
        job_queue.push(std::move(task));
    }

};

#endif //SOCKET_SERVER_V2_WORKERPOOL_H