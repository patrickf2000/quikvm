#pragma once

#include <vector>
#include <string>

std::vector<std::string> load_file(const char *path);
std::vector<std::string> load_multiple(std::vector<char *> *paths);
