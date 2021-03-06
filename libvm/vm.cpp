#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <unistd.h>
#include <dlfcn.h>

#include <bytecode.hh>

#include "vm.hh"
#include "reader.hh"
#include "loader.hh"

std::vector<Instr> instructions;
std::set<unsigned char> int_codes = {I_LOAD, I_CMP, I_VAR, I_STORE, I_LOAD_VAR,
			I_ARRAY, I_LOAD_ARR,
			D_CMP, D_VAR, D_STORE, D_LOAD_VAR,
			JMP, JE, JNE, JG, JL, JGE, JLE,
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
		} else if (i.opcode == ByteCode::I_STORE2 
				|| i.opcode == ByteCode::I_LOAD_ARR2) {
			i.i_arg = reader.read_int();
			i.i_arg2 = reader.read_int();
		} else if (i.opcode == ByteCode::D_LOAD) {
			i.d_arg = reader.read_double();
		} else if (i.opcode == ByteCode::S_LOAD || i.opcode == ByteCode::EXCALL) {
			i.s_arg = reader.read_str();
		} else if (i.opcode == ByteCode::LIB) {
			std::string cmd;
			cmd += reader.read_opcode();
			cmd += reader.read_opcode();
			cmd += reader.read_str();
			cmd += ';';
			cmd += reader.read_str();
			lib(cmd);
			continue;
		}
		
		instructions.push_back(i);
	}
	
	reader.close();
}

//Runs the virtual machine
void run(int pc, bool dump) {
	Context c;
	
	int cmp = 0;
	int counter = pc;
	
	while (counter < instructions.size()) {
		auto i = instructions.at(counter);
		
		//Dump requested info
		if (dump) {
			std::cout << "PC: " << counter << " OUT " << instructions.size() << std::endl;
			printf("OPx: %x\n", i.opcode);
			std::cout << std::endl;
		}
		
		switch (i.opcode) {
			case ByteCode::I_LOAD: c.int_stack.push(i.i_arg); break;
			case ByteCode::I_PRINT: std::cout << c.int_stack.top() << std::endl; break;
			case ByteCode::I_VAR:
			case ByteCode::I_ARRAY:
			case ByteCode::D_VAR: c.memory.insert(std::pair<int, std::string>(i.i_arg, "")); break;
			case ByteCode::I_STORE: {
					c.memory[i.i_arg] = std::to_string(c.int_stack.top()); 
					c.int_stack.pop();
				} break;
			case ByteCode::I_STORE2: {
					int addr = i.i_arg;
					addr += std::stoi(c.memory[i.i_arg2]);
					c.memory[addr] = std::to_string(c.int_stack.top());
					c.int_stack.pop();
				} break;
			case ByteCode::I_LOAD_ARR:
			case ByteCode::I_LOAD_VAR: {
					int item = std::stoi(c.memory[i.i_arg]);
					c.int_stack.push(item);
				} break;
			case ByteCode::I_LOAD_ARR2: {
					int addr = i.i_arg;
					addr += std::stoi(c.memory[i.i_arg2]);
					int item = std::stoi(c.memory[addr]);
					c.int_stack.push(item);
				} break;
			case ByteCode::I_INPUT: {
					int i;
					std::cin >> i;
					c.int_stack.push(i);
				} break;
			case ByteCode::I_CMP: {
					if (c.int_stack.top() > i.i_arg)
						cmp = 1;
					else if (c.int_stack.top() < i.i_arg)
						cmp = -1;
					else
						cmp = 0;
				} break;

			case ByteCode::I_ADD:
			case ByteCode::I_SUB:
			case ByteCode::I_MUL:
			case ByteCode::I_DIV:
			case ByteCode::I_MOD: {
					int no1 = c.int_stack.top();
					c.int_stack.pop();
					int no2 = c.int_stack.top();
					c.int_stack.pop();
					int answer = 0;
					
					switch (i.opcode) {
						case ByteCode::I_ADD: answer = no1+no2; break;
						case ByteCode::I_SUB: answer = no1-no2; break;
						case ByteCode::I_MUL: answer = no1*no2; break;
						case ByteCode::I_DIV: answer = no1/no2; break;
						default: answer = no1%no2;
					}
					
					c.int_stack.push(answer);
				} break;
			case ByteCode::I_POP: c.int_stack.pop(); break;
			
			case ByteCode::D_LOAD: c.flt_stack.push(i.d_arg); break;
			case ByteCode::D_PRINT: std::cout << c.flt_stack.top() << std::endl; break;
			case ByteCode::D_STORE: {
					c.memory[i.i_arg] = std::to_string(c.flt_stack.top()); 
					c.flt_stack.pop();
				} break;
			case ByteCode::D_LOAD_VAR: {
					double item = std::stod(c.memory[i.i_arg]);
					c.flt_stack.push(item);
				} break;
			case ByteCode::D_INPUT: {
					double d;
					std::cin >> d;
					c.flt_stack.push(d);
				} break;
				
			case ByteCode::D_ADD:
			case ByteCode::D_SUB:
			case ByteCode::D_MUL:
			case ByteCode::D_DIV: {
					double no1 = c.flt_stack.top();
					c.flt_stack.pop();
					double no2 = c.flt_stack.top();
					c.flt_stack.pop();
					double answer = 0;
					
					switch (i.opcode) {
						case ByteCode::D_ADD: answer = no1+no2; break;
						case ByteCode::D_SUB: answer = no1-no2; break;
						case ByteCode::D_MUL: answer = no1*no2; break;
						case ByteCode::D_DIV: answer = no1/no2; break;
					}
					
					c.flt_stack.push(answer);
				} break;
			case ByteCode::D_POP: c.flt_stack.pop(); break;
			
			case ByteCode::S_LOAD: c.str_stack.push(i.s_arg); break;
			case ByteCode::S_PRINT: std::cout << c.str_stack.top() << std::endl; break;
			case ByteCode::S_POP: c.str_stack.pop(); break;
			
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
					std::thread thr(run, i.i_arg, dump); 
					thr.join();
				} break;
				
			case ByteCode::CALL: {
					c.call_stack.push(counter+1);
					counter = i.i_arg;
					continue;
				}
				
			case ByteCode::RET: {
					counter = c.call_stack.top();
					c.call_stack.pop();
					continue;
				}
				
			case ByteCode::EXCALL: {
					excall(i.s_arg, &c);
				} break;
				
			case ByteCode::EXIT: counter = instructions.size()+1; break;
			case 0: break;
			default: {
				std::cout << "Fatal: Unknown instruction." << std::endl;
				std::cout << "We cannot continue." << std::endl;
				std::cout << std::endl;
				std::cout << "Current instruction:" << std::endl;
				printf("%x\n", i.opcode);
				break;
			}
		}
		
		++counter;
	}
	
	//Clean up any loaded libraries
	for (auto const& i : open_libs) {
		dlclose(i.second.handle);
	}
	
	//If requested, dump the memory
	if (dump) {
		std::cout << "MAIN MEMORY DUMP" << std::endl;
		
		for (int i = 0; i<c.memory.size(); i++) {
			std::cout << "[" << i << "] -> ";
			std::cout << c.memory[i] << std::endl;
		}
		
		std::cout << std::endl;
		std::cout << "Dumping complete." << std::endl;
	}
}

void run_start(bool dump) {
	run(start_loco, dump);
}
