#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

#include <bytecode.hh>

#include "vm.hh"
#include "reader.hh"

struct Instr {
	unsigned char opcode;
	int i_arg;
	double d_arg;
	std::string s_arg;
};

std::vector<Instr> instructions;

//Loads the file
void load(const char *path) {
	BinReader reader(path);
	Instr i;
	
	while (!reader.is_eof()) {
		i.opcode = reader.read_opcode();
		
		if (i.opcode == ByteCode::I_LOAD || i.opcode == ByteCode::I_CMP) {
			i.i_arg = reader.read_int();
		} else if (i.opcode == ByteCode::D_LOAD) {
			i.d_arg = reader.read_double();
		} else if (i.opcode == ByteCode::S_LOAD) {
			i.s_arg = reader.read_str();
		} else if (i.opcode == ByteCode::LBL || i.opcode == ByteCode::JMP
				|| i.opcode == ByteCode::JE) {
			i.i_arg = reader.read_int();
		}
		
		instructions.push_back(i);
	}
	
	reader.close();
}

//Runs the virtual machine
void run() {
	std::stack<int> int_stack;
	std::stack<double> flt_stack;
	std::stack<std::string> str_stack;
	int cmp = 0;
	int counter = 0;
	
	while (counter < instructions.size()) {
		auto i = instructions.at(counter);
		
		switch (i.opcode) {
			case ByteCode::I_LOAD: int_stack.push(i.i_arg); break;
			case ByteCode::I_PRINT: std::cout << int_stack.top() << std::endl; break;
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
			
			case ByteCode::D_LOAD: flt_stack.push(i.d_arg); break;
			case ByteCode::D_PRINT: std::cout << flt_stack.top() << std::endl; break;
			case ByteCode::D_INPUT: {
					double d;
					std::cin >> d;
					flt_stack.push(d);
				} break;
			
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
			case ByteCode::EXIT: std::exit(0);
		}
		
		++counter;
	}
}
