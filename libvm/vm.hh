#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>
#include <set>

#include <bytecode.hh>

struct Context {
	std::map<int, std::string> memory;
	std::stack<int> int_stack;
	std::stack<double> flt_stack;
	std::stack<std::string> str_stack;
	std::stack<int> call_stack;
};

struct Instr {
	unsigned char opcode;
	int i_arg;
	double d_arg;
	std::string s_arg;
};

extern std::vector<Instr> instructions;
extern std::set<unsigned char> int_codes;

void load(const char *path);
void run(int pc, bool dump);
void run_start(bool dump);
