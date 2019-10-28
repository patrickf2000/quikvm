#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include <bytecode.hh>

#include "reader.hh"
#include "types.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input specified!" << std::endl;
		return 1;
	}
	
	auto path = std::string(argv[1]);
	
	BinReader reader(path.c_str());
	std::vector<Instr> instructions;
	Instr i;
	
	while (!reader.is_eof()) {
		i.opcode = reader.read_opcode();
		
		if (i.opcode == ByteCode::I_LOAD) {
			i.i_arg = reader.read_int();
		} else if (i.opcode == ByteCode::D_LOAD) {
			i.d_arg = reader.read_double();
		}
		
		instructions.push_back(i);
	}
	
	reader.close();
	
	std::stack<std::string> runtime;
	
	for (auto i : instructions) {
		switch (i.opcode) {
			case ByteCode::I_LOAD: runtime.push(std::to_string(i.i_arg)); break;
			case ByteCode::I_PRINT: std::cout << runtime.top() << std::endl; break;
			case ByteCode::D_LOAD: runtime.push(std::to_string(i.d_arg)); break;
			case ByteCode::D_PRINT: std::cout << runtime.top() << std::endl; break;
			case ByteCode::EXIT: std::exit(0);
		}
	}
	
	return 0;
}
