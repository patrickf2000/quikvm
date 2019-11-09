#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <unistd.h>

#include <bytecode.hh>

#include "vm.hh"
#include "reader.hh"
#include "loader.hh"

struct Instr {
	unsigned char opcode;
	int i_arg;
	double d_arg;
	std::string s_arg;
};

std::vector<Instr> instructions;
std::set<unsigned char> int_codes = {I_LOAD, I_CMP, I_VAR, I_STORE, I_LOAD_VAR,
			D_CMP, D_VAR, D_STORE, D_LOAD_VAR,
			LBL, JMP, JE, JNE, JG, JL, JGE, JLE,
			CALL, SLEEP, NEW_THREAD};
			
int start_loco = 0;

//Loads the file
void load(const char *path) {
	BinReader reader(path);
	Instr i;
	
	while (!reader.is_eof()) {
		i.opcode = reader.read_opcode();
		
		if (i.opcode == ByteCode::START) {
			start_loco = reader.read_int();
			continue;
		} else if (int_codes.find(i.opcode) != int_codes.end()) {
			i.i_arg = reader.read_int();
		} else if (i.opcode == ByteCode::D_LOAD) {
			i.d_arg = reader.read_double();
		} else if (i.opcode == ByteCode::S_LOAD) {
			i.s_arg = reader.read_str();
		} else if (i.opcode == ByteCode::EXCALL) {
			i.s_arg = reader.read_str();
		}
		
		instructions.push_back(i);
	}
	
	reader.close();
}

//Runs the virtual machine
void run(int pc) {
	std::map<int, std::string> memory;

	std::stack<int> int_stack;
	std::stack<double> flt_stack;
	std::stack<std::string> str_stack;
	std::stack<int> call_stack;
	
	int cmp = 0;
	int counter = pc;
	
	while (counter < instructions.size()) {
		auto i = instructions.at(counter);
		
		switch (i.opcode) {
			case ByteCode::I_LOAD: int_stack.push(i.i_arg); break;
			case ByteCode::I_PRINT: std::cout << int_stack.top() << std::endl; break;
			case ByteCode::I_VAR:
			case ByteCode::D_VAR: memory.insert(std::pair<int, std::string>(i.i_arg, "")); break;
			case ByteCode::I_STORE: {
					memory[i.i_arg] = std::to_string(int_stack.top()); 
					int_stack.pop();
				} break;
			case ByteCode::I_LOAD_VAR: {
					int item = std::stoi(memory[i.i_arg]);
					int_stack.push(item);
				} break;
			case ByteCode::I_INPUT: {
					int i;
					std::cin >> i;
					int_stack.push(i);
				} break;
			case ByteCode::I_CMP: {
					if (int_stack.top() > i.i_arg)
						cmp = 1;
					else if (int_stack.top() < i.i_arg)
						cmp = -1;
					else
						cmp = 0;
				} break;

			case ByteCode::I_ADD:
			case ByteCode::I_SUB:
			case ByteCode::I_MUL:
			case ByteCode::I_DIV:
			case ByteCode::I_MOD: {
					int no1 = int_stack.top();
					int_stack.pop();
					int no2 = int_stack.top();
					int_stack.pop();
					int answer = 0;
					
					switch (i.opcode) {
						case ByteCode::I_ADD: answer = no1+no2; break;
						case ByteCode::I_SUB: answer = no1-no2; break;
						case ByteCode::I_MUL: answer = no1*no2; break;
						case ByteCode::I_DIV: answer = no1/no2; break;
						default: answer = no1%no2;
					}
					
					int_stack.push(answer);
				} break;
			case ByteCode::I_POP: int_stack.pop(); break;
			
			case ByteCode::D_LOAD: flt_stack.push(i.d_arg); break;
			case ByteCode::D_PRINT: std::cout << flt_stack.top() << std::endl; break;
			case ByteCode::D_STORE: {
					memory[i.i_arg] = std::to_string(flt_stack.top()); 
					flt_stack.pop();
				} break;
			case ByteCode::D_LOAD_VAR: {
					double item = std::stod(memory[i.i_arg]);
					flt_stack.push(item);
				} break;
			case ByteCode::D_INPUT: {
					double d;
					std::cin >> d;
					flt_stack.push(d);
				} break;
				
			case ByteCode::D_ADD:
			case ByteCode::D_SUB:
			case ByteCode::D_MUL:
			case ByteCode::D_DIV: {
					double no1 = flt_stack.top();
					flt_stack.pop();
					double no2 = flt_stack.top();
					flt_stack.pop();
					double answer = 0;
					
					switch (i.opcode) {
						case ByteCode::D_ADD: answer = no1+no2; break;
						case ByteCode::D_SUB: answer = no1-no2; break;
						case ByteCode::D_MUL: answer = no1*no2; break;
						case ByteCode::D_DIV: answer = no1/no2; break;
					}
					
					flt_stack.push(answer);
				} break;
			case ByteCode::D_POP: flt_stack.pop(); break;
			
			case ByteCode::S_LOAD: str_stack.push(i.s_arg); break;
			case ByteCode::S_PRINT: std::cout << str_stack.top() << std::endl; break;
			case ByteCode::S_POP: str_stack.pop(); break;
			
			case ByteCode::JMP: counter = i.i_arg; continue;
			case ByteCode::JE: {
					if (cmp == 0) {
						counter = i.i_arg;
						continue;
					}
				} break;
			case ByteCode::JNE: {
					if (cmp != 0) {
						counter = i.i_arg;
						continue;
					}
				} break;
			case ByteCode::JG: {
					if (cmp == 1) {
						counter = i.i_arg;
						continue;
					}
				} break;
			case ByteCode::JL: {
					if (cmp == -1) {
						counter = i.i_arg;
						continue;
					}
				} break;
			case ByteCode::JGE: {
					if (cmp >= 0) {
						counter = i.i_arg;
						continue;
					}
				} break;
			case ByteCode::JLE: {
					if (cmp <= 0) {
						counter = i.i_arg;
						continue;
					}
				} break;
				
			case ByteCode::SLEEP: sleep(i.i_arg); break;
			case ByteCode::NEW_THREAD: {
					std::thread thr(run, i.i_arg); 
					thr.join();
				} break;
				
			case ByteCode::CALL: {
					call_stack.push(counter+1);
					counter = i.i_arg;
					continue;
				}
				
			case ByteCode::RET: {
					counter = call_stack.top();
					call_stack.pop();
					continue;
				}
				
			case ByteCode::EXCALL: {
					excall(i.s_arg, &int_stack);
				} break;
				
			case ByteCode::EXIT: std::exit(0);
		}
		
		++counter;
	}
}

void run_start() {
	run(start_loco);
}
