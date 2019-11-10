#pragma once

#include <string>
#include <stack>

#include "vm.hh"

struct Func {
	void *handle;
	std::string lib;
	std::string func_name;
	unsigned char type;
	unsigned char ret;
};

extern std::map<std::string, Func> open_libs;

void lib(std::string cmd);
void excall(std::string name, Context *context);
