#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string read_file(const std::string &path);
std::string get_content_type(const std::string &path);
void log_message(const std::string &msg);

#endif