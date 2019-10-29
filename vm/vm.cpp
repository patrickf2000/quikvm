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
		
		if (i.opcode == ByteCode::I_LOAD) {
			i.i_arg = reader.read_int();
		} else if (i.opcode == ByteCode::D_LOAD) {
			i.d_arg = reader.read_double();
		} else if (i.opcode == ByteCode::S_LOAD) {
			i.s_arg = reader.read_str();
		} else if (i.opcode == ByteCode::LBL || i.opcode == ByteCode::JMP) {
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
	int counter = 0;
	
	while (counter < instructions.size()) {
		auto i = instructions.at(counter);
		
		switch (i.opcode) {
			case ByteCode::I_LOAD: int_stack.push(i.i_arg); break;
			case ByteCode::I_PRINT: std::cout << int_stack.top() << std::endl; break;
			
			case ByteCode::D_LOAD: flt_stack.push(i.d_arg); break;
			case ByteCode::D_PRINT: std::cout << flt_stack.top() << std::endl; break;
			
			case ByteCode::S_LOAD: str_stack.push(i.s_arg); break;
			case ByteCode::S_PRINT: std::cout << str_stack.top() << std::endl; break;
			
			case ByteCode::JMP: counter = i.i_arg; continue;
			case ByteCode::EXIT: std::exit(0);
		}
		
		++counter;
	}
}
