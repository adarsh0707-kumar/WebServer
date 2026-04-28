#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <sstream>
#include <fstream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "../inc/handler.h"
#include "../inc/server.h"

using namespace std;

queue<int> client_queue;
mutex queue_mutex;
condition_variable cv;

void worker()
{
    while (true)
    {
        int client_socket;
        {
            unique_lock<mutex> lock(queue_mutex);

            cv.wait(lock, []
                    { return !client_queue.empty(); });
            client_socket = client_queue.front();
            client_queue.pop();
        }
        handle_client(client_socket);
    }
}

string read_file(const string &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        return "";
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

void log(const string& message){
    time_t now = time(nullptr);
    log_file << ctime(&now) << " : "<< message << endl;
}

void load_config(){
    ifstream file("../config.txt");
    string line;

    while (true)
    {
        auto pos = line.find('=');
        if(pos != string::npos){
            config[line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
}

void handle_client(int client_socket)
{
    char buffer[30000] = {0};

    read(client_socket, buffer, 30000);

    string request(buffer);

    // Extract first line of the request

    istringstream stream(request);
    string method, path, version;
    stream >> method >> path >> version;

    cout << "Method: " << method << ", Path: " << path << endl;

    string response;

    string file_path = "../www";

    if (path == "/")
    {
        file_path += "/index.html";
    }
    else
    {
        file_path += path + ".html";
    }
    log("New request: " + path);
    string body = read_file(file_path);
    if (!body.empty())
    {
        response =
            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + body;
    }
    else
    {
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

    const int THREAD_COUNT = 4;
    vector<thread> pool;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pool.emplace_back(worker);
    }

    bind(server_fd, (struct sockaddr *)&address, addrlen);

    listen(server_fd, 10);

    cout << "HTTP Server is running on port 8080..." << endl;

    while (true)
    {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

        {
            lock_guard<mutex> lock(queue_mutex);
            client_queue.push(client_socket);
            cv.notify_one();
        }
    }

    close(server_fd);
    return 0;
}
