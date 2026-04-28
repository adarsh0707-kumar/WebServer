#include "../inc/server.h"
#include "../inc/thread_pool.h"
#include "../inc/utils.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

Server::Server(int port, int threads)
{
    this->port = port;
    this->thread_count = threads;
}

void Server::start()
{
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "Server running on port " << port << std::endl;

    ThreadPool pool(thread_count);

    while (true)
    {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        log_message("New client connected");
        pool.enqueue(client_socket);
    }

    close(server_fd);
}