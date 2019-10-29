#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <bytecode.hh>

#include "writer.hh"
#include "assembler.hh"

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
	std::vector<std::string> contents;
	
	while (std::getline(reader, ln)) {
		contents.push_back(ln);
	}
	
	contents = pass1(contents);
	
	for (auto ln : contents) {
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		//Integer operations
		if (op == "i_load") {
			writer.write_opcode(ByteCode::I_LOAD);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_print") {
			writer.write_opcode(ByteCode::I_PRINT);
		} else if (op == "i_input") {
			writer.write_opcode(ByteCode::I_INPUT);
		} else if (op == "i_cmp") {
			writer.write_opcode(ByteCode::I_CMP);
			writer.write_int(std::stoi(arg));
			
		//Double operations
		} else if (op == "d_load") {
			writer.write_opcode(ByteCode::D_LOAD);
			writer.write_double(std::stod(arg));
		} else if (op == "d_print") {
			writer.write_opcode(ByteCode::D_PRINT);
		} else if (op == "d_input") {
			writer.write_opcode(ByteCode::D_INPUT);
			
		//String operations
		} else if (op == "s_load") {
			writer.write_opcode(ByteCode::S_LOAD);
			auto s = arg.substr(1, arg.length()-2);
			writer.write_str(s.c_str());
		} else if (op == "s_print") {
			writer.write_opcode(ByteCode::S_PRINT);
		} else if (op == "s_pop") {
			writer.write_opcode(ByteCode::S_POP);
			
		//Flow control
		} else if (op == "lbl") {
			writer.write_opcode(ByteCode::LBL);
			writer.write_int(std::stoi(arg));
		} else if (op == "jmp") {
			writer.write_opcode(ByteCode::JMP);
			writer.write_int(std::stoi(arg));
		} else if (op == "je") {
			writer.write_opcode(ByteCode::JE);
			writer.write_int(std::stoi(arg));
			
		//Other
		} else if (op == "exit") {
			writer.write_opcode(ByteCode::EXIT);
		}
	}
	
	reader.close();	
	return 0;
}
