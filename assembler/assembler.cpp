#include <bytecode.hh>

#include "assembler.hh"
#include "writer.hh"

std::map<std::string, int> symbols;
std::map<std::string, int> vars;

void pass1(std::vector<std::string> *contents) {
	std::vector<std::string> ret;
	int var_index = 0;

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		if (op == "lbl") {
			symbols.insert(std::pair<std::string, int>(arg, i));
			ln = op + " " + std::to_string(i);
		} else if (op == "i_var") {
			vars.insert(std::pair<std::string, int>(arg, var_index));
			ln = op + " " + std::to_string(var_index);
			++var_index;
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
		} else if (op == "i_store" || op == "i_load_var") {
			ln = op + " ";
			ln += std::to_string(vars.at(arg));
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}
}

void pass2(std::vector<std::string> *contents, std::string path) {
	//First, build the path and open the writer
	std::string name = "";
	
	int spos = path.find_last_of("/");
	if (spos == -1) {
		spos = 0;
	}
	
	int ppos = path.find_last_of(".");
	if (ppos == -1) {
		ppos = path.length()-1;
	}
	
	name = path.substr(spos+1, (ppos-spos));
	path = name + "bin";
	
	BinWriter writer(path.c_str());
	
	//Now, assemble
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
		} else if (op == "i_var") {
			writer.write_opcode(ByteCode::I_VAR);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_store") {
			writer.write_opcode(ByteCode::I_STORE);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_load_var") {
			writer.write_opcode(ByteCode::I_LOAD_VAR);
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
