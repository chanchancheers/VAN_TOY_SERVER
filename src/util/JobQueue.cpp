
#include "../../include/util/JobQueue.h"

template<typename T>
void JobQueue<T>::push(T data) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue.push(std::move(data));
    }
    cv.notify_one(); // cv.wait으로 대기중인 스레드 중 1개를 깨워서 작업을 진행하되, wait의 콜백함수를 다시 확인 후 진행.
}

template<typename T>
T JobQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mutex_);

    cv.wait(lock, [this]()->bool { // mutex 해제, 호출 thread 대기열에 추가
       return !queue.empty();
    });

    T data = std::move(queue.front());
    queue.pop();
    return data;
}