#include "../inc/thread_pool.h"
#include "../inc/http_handler.h"

ThreadPool::ThreadPool(int num_threads)
{
    for (int i = 0; i < num_threads; i++)
    {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

void ThreadPool::enqueue(int client_socket)
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        tasks.push(client_socket);
    }
    cv.notify_one();
}

void ThreadPool::worker()
{
    while (true)
    {
        int client_socket;

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this]
                    { return !tasks.empty(); });

            client_socket = tasks.front();
            tasks.pop();
        }

        handle_client(client_socket);
    }
}