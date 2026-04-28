#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
    ThreadPool(int num_threads);
    void enqueue(int client_socket);

private:
    std::vector<std::thread> workers;
    std::queue<int> tasks;

    std::mutex queue_mutex;
    std::condition_variable cv;

    void worker();
};

#endif