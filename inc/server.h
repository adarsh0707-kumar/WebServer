#ifndef SERVER_H
#define SERVER_H

#include <queue>
#include <mutex>
#include <condition_variable>

extern std::queue<int> client_queue;
extern std::mutex queue_mutex;
extern std::condition_variable cv;

void worker();

#endif // SERVER_H
