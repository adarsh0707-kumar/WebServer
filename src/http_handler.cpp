#include "../inc/http_handler.h"
#include "../inc/utils.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <string>

void handle_client(int client_socket)
{
    char buffer[30000] = {0};
    read(client_socket, buffer, 30000);

    std::string request(buffer);

    std::istringstream stream(request);
    std::string method, path, version;
    stream >> method >> path >> version;

    log_message("Request: " + method + " " + path);

    if (path.find("..") != std::string::npos)
    {
        close(client_socket);
        return;
    }

    std::string file_path = "./www";

    if (path == "/")
        file_path += "/index.html";
    else
        file_path += path + ".html";

    std::string body = read_file(file_path);

    std::string response;

    if (!body.empty())
    {
        response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: " +
            get_content_type(file_path) + "\r\n" +
            "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n" +
            body;
    }
    else
    {
        std::string not_found = "<h1>404 Not Found</h1>";
        response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            std::to_string(not_found.size()) + "\r\n\r\n" +
            not_found;
    }

    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
}