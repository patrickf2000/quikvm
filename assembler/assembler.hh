#pragma once

#include <map>
#include <string>
#include <vector>

extern std::map<std::string, int> symbols;

void pass1(std::vector<std::string> *contents, bool p1);
void pass2(std::vector<std::string> *contents, std::string path);
