#include <iostream>
#include <string>
#include <fstream>

#include <bytecode.hh>

#include "writer.hh"
#include "parser.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input file specified" << std::endl;
		return 1;
	}
	
	auto input = std::string(argv[1]);
	std::string ln = "";
	
	std::ifstream reader(input.c_str());
	if (!reader.is_open()) {
		std::cout << "Fatal: Unable to open input file." << std::endl;
		return 1;
	}
	
	BinWriter writer("out.bin");
	
	while (std::getline(reader, ln)) {
		auto op = get_operand(ln);
		auto arg = get_arg(ln);
		
		if (op == "i_load") {
			writer.write_opcode(ByteCode::I_LOAD);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_print") {
			writer.write_opcode(ByteCode::I_PRINT);
		} else if (op == "d_load") {
			writer.write_opcode(ByteCode::D_LOAD);
			writer.write_double(std::stod(arg));
		} else if (op == "d_print") {
			writer.write_opcode(ByteCode::D_PRINT);
		} else if (op == "exit") {
			writer.write_opcode(ByteCode::EXIT);
		}
	}
	
	reader.close();	
	return 0;
}
