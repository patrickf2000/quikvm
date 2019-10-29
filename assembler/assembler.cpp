#include <bytecode.hh>

#include "assembler.hh"
#include "writer.hh"

std::map<std::string, int> symbols;

void pass1(std::vector<std::string> *contents) {
	std::vector<std::string> ret;

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		if (op == "lbl") {
			symbols.insert(std::pair<std::string, int>(arg, i));
			ln = op + " " + std::to_string(i);
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);

		if (op == "jmp" || op == "je") {
			ln = op + " ";
			ln += std::to_string(symbols.at(arg));
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}
}

void pass2(std::vector<std::string> *contents) {
	BinWriter writer("out.bin");
	
	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
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
}
