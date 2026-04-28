#ifndef SERVER_H
#define SERVER_H

class Server
{
public:
    Server(int port, int threads);
    void start();

private:
    int port;
    int thread_count;
};

#endif