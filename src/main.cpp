#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server running on port 8080...\n";

    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    char buffer[30000] = {0};
    read(client_socket, buffer, 30000);

    std::cout << buffer << std::endl;

    const char *response =
        "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Hello World</h1>";

    send(client_socket, response, strlen(response), 0);

    close(client_socket);
    close(server_fd);

    return 0;
}