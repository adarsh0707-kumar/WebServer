#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <fstream>
#include <ctime>
#include <map>

std::string read_file(const std::string &path);
std::ofstream log_file("server.log", std::ios::app);
std::map<std::string, std::string> config;

void log(const std::string &message);
void handle_client(int client_socket);
void load_config();

#endif // HANDLER_H
