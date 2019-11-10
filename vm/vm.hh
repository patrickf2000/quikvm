#pragma once

#include <map>
#include <stack>
#include <string>

struct Context {
	std::map<int, std::string> memory;
	std::stack<int> int_stack;
	std::stack<double> flt_stack;
	std::stack<std::string> str_stack;
	std::stack<int> call_stack;
};

void load(const char *path);
void run(int pc, bool dump);
void run_start(bool dump);
