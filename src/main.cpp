#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include<sstream>

using namespace std;

void handle_client(int client_socket)
{
    char buffer[30000] = {0};

    read(client_socket, buffer, 30000);

    string request(buffer);

    //Extract first line of the request

    istringstream stream(request);
    string method, path, version;
    stream >> method >> path >> version;

    cout << "Method: " << method << ", Path: " << path << endl;

    string response;

    if(path == "/"){
        response =
            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
            "<h1>Home Page<h1>";
    }
    else if(path == "/about"){
        response =
            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
            "<h1>About Page<h1>";
    }
    else{
        response =
            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
            "<h1>404 Not Found</h1>";
    }

    send(client_socket, response.c_str(), response.size(), 0);

    close(client_socket);
}

int main()
{
    int server_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, addrlen);

    listen(server_fd, 10);

    cout << "HTTP Server is running on port 8080..." << endl;

    while (true)
    {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

        thread t(handle_client, client_socket);
        t.detach();
    }

    close(server_fd);
    return 0;
}
