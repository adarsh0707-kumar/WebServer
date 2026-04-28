#ifndef HANDLER_H
#define HANDLER_H

#include <string>

std::string read_file(const std::string &path);
void handle_client(int client_socket);

#endif // HANDLER_H
