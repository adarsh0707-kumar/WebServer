#include "../inc/utils.h"
#include <fstream>
#include <iostream>
#include <ctime>

std::ofstream log_file("server.log", std::ios::app);

std::string read_file(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return "";

    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

std::string get_content_type(const std::string &path)
{
    if (path.find(".html") != std::string::npos)
        return "text/html";
    if (path.find(".css") != std::string::npos)
        return "text/css";
    if (path.find(".js") != std::string::npos)
        return "application/javascript";
    if (path.find(".png") != std::string::npos)
        return "image/png";
    return "text/plain";
}

void log_message(const std::string &msg)
{
    std::time_t now = std::time(nullptr);
    log_file << std::ctime(&now) << ": " << msg << std::endl;
}