//
// Created by 신은찬 on 6/3/26.
#include "../../../include/network/server/WorkerPool.h"
#include <thread>
#include "../../include/dto/Task.h"
#include "../../../include/dto/Task.h"
#include "../../../include/network/server/Notifier.h"


WorkerPool::WorkerPool(size_t size) {
    for (int i = 0; i < size; i++) {
        workers.emplace_back([this]()->void {
           this->doWorkerLoop();
        });
    }
}

void WorkerPool::doWorkerLoop() {
    while (true) {
        auto task = jobQueue.front();
        jobQueue.pop();

        Task result = processTask(task);
        if (result.isSuccess()) {
            resultQueue.push(result);
            //TODO wakeup call
        }
    }
}
//TODO 태스크를 처리하고 새로운 정보를 담아서 다시 리턴
Task WorkerPool::processTask(Task task) {
    return task;
}

