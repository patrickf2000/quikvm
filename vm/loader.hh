#pragma once

#include <string>
#include <stack>

#include "vm.hh"

extern std::map<std::string, void *> open_libs;

void excall(std::string cmd, Context *context);
