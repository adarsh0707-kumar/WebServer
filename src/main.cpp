#include "../inc/server.h"

int main()
{
    int port = 8080;
    int threads = 4;

    Server server(port, threads);
    server.start();

    return 0;
}