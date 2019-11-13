#include <iostream>
#include <string.h>
#include <cstdlib>

#include <bytecode.hh>

#include "assembler.hh"
#include "writer.hh"

std::map<std::string, int> symbols;
std::map<std::string, int> vars;
int start_loco;

//Assign numbers to labels and variables
void pass1(std::vector<std::string> *contents, bool p1) {
	std::vector<std::string> ret;
	int var_index = 0;

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		if (op == "lbl") {
			if (arg == "_start")
				start_loco = i;
			
			symbols.insert(std::pair<std::string, int>(arg, i));
			ln = op + " " + std::to_string(i);
			
			contents->erase(contents->begin()+i);
			continue;
		} else if (op == "i_var" || op == "d_var") {
			vars.insert(std::pair<std::string, int>(arg, var_index));
			ln = op + " " + std::to_string(var_index);
			++var_index;
		} else if (op == "i_array") {
			std::string name = strtok((char *)arg.c_str(), " ");
			int len = std::stoi(strtok(NULL, " "));
			
			vars.insert(std::pair<std::string, int>(name, var_index));
			ln = op + " " + std::to_string(var_index);
			var_index += len;
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);

		if (op == "jmp" || op == "je" || op == "jne" || op == "jg"
			|| op == "jl" || op == "jge" || op == "jle" || op == "call"
			|| op == "new_thread") {
			ln = op + " ";
			ln += std::to_string(symbols[arg]);
		} else if (op == "i_store" || op == "i_load_var"
				|| op == "i_load_arr"
				|| op == "d_store" || op == "d_load_var") {
			if (arg.find("+") != std::string::npos) {
				std::string name = strtok((char *)arg.c_str(), "+");
				std::string offset = strtok(NULL, " ");
				int addr = vars[name];
				
				if (vars.find(offset) != vars.end()) {
					if (op == "i_store")
						ln = "i_store2 ";
					else if (op == "i_load_arr")
						ln = "i_load_arr2 ";
						
					ln += std::to_string(addr);
					ln += " ";
					ln += std::to_string(vars[offset]);
				} else {
					ln = op + " ";	
					addr += std::stoi(offset);
					ln += std::to_string(addr);
				}
			} else {
				ln = op + " ";
				ln += std::to_string(vars[arg]);
				
				if (op == "i_load_arr")
					ln += " 0";
			}
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}
	
	//debug
	if (p1) {
		for (int i = 0; i<contents->size(); i++) {
			std::cout << "[DB] " << i << ": " << contents->at(i) << std::endl;
		}
		
		std::exit(0);
	}
}

//Assemble and write the binary file
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
	
	if (start_loco != 0) {
		writer.write_opcode(ByteCode::START);
		writer.write_int(start_loco);
	}
	
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
		} else if (op == "i_add") {
			writer.write_opcode(ByteCode::I_ADD);
		} else if (op == "i_sub") {
			writer.write_opcode(ByteCode::I_SUB);
		} else if (op == "i_mul") {
			writer.write_opcode(ByteCode::I_MUL);
		} else if (op == "i_div") {
			writer.write_opcode(ByteCode::I_DIV);
		} else if (op == "i_mod") {
			writer.write_opcode(ByteCode::I_MOD);
		} else if (op == "i_pop") {
			writer.write_opcode(ByteCode::I_POP);
		} else if (op == "i_array") {
			writer.write_opcode(ByteCode::I_ARRAY);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_store2") {
			writer.write_opcode(ByteCode::I_STORE2);
			
			std::string p1 = strtok((char *)arg.c_str(), " ");
			std::string p2 = strtok(NULL, " ");
			writer.write_int(std::stoi(p1));
			writer.write_int(std::stoi(p2));
		} else if (op == "i_load_arr") {
			writer.write_opcode(ByteCode::I_LOAD_ARR);
			writer.write_int(std::stoi(arg));
		} else if (op == "i_load_arr2") {
			writer.write_opcode(ByteCode::I_LOAD_ARR2);
			
			std::string p1 = strtok((char *)arg.c_str(), " ");
			std::string p2 = strtok(NULL, " ");
			writer.write_int(std::stoi(p1));
			writer.write_int(std::stoi(p2));
			
		//Double operations
		} else if (op == "d_load") {
			writer.write_opcode(ByteCode::D_LOAD);
			writer.write_double(std::stod(arg));
		} else if (op == "d_print") {
			writer.write_opcode(ByteCode::D_PRINT);
		} else if (op == "d_input") {
			writer.write_opcode(ByteCode::D_INPUT);
		} else if (op == "d_cmp") {
			writer.write_opcode(ByteCode::D_CMP);
			writer.write_int(std::stoi(arg));
		} else if (op == "d_var") {
			writer.write_opcode(ByteCode::D_VAR);
			writer.write_int(std::stoi(arg));
		} else if (op == "d_store") {
			writer.write_opcode(ByteCode::D_STORE);
			writer.write_int(std::stoi(arg));
		} else if (op == "d_load_var") {
			writer.write_opcode(ByteCode::D_LOAD_VAR);
			writer.write_int(std::stoi(arg));
		} else if (op == "d_add") {
			writer.write_opcode(ByteCode::D_ADD);
		} else if (op == "d_sub") {
			writer.write_opcode(ByteCode::D_SUB);
		} else if (op == "d_mul") {
			writer.write_opcode(ByteCode::D_MUL);
		} else if (op == "d_div") {
			writer.write_opcode(ByteCode::D_DIV);
		} else if (op == "d_pop") {
			writer.write_opcode(ByteCode::D_POP);
			
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
		} else if (op == "jmp") {
			writer.write_opcode(ByteCode::JMP);
			writer.write_int(std::stoi(arg));
		} else if (op == "je") {
			writer.write_opcode(ByteCode::JE);
			writer.write_int(std::stoi(arg));
		} else if (op == "jne") {
			writer.write_opcode(ByteCode::JNE);
			writer.write_int(std::stoi(arg));
		} else if (op == "jg") {
			writer.write_opcode(ByteCode::JG);
			writer.write_int(std::stoi(arg));
		} else if (op == "jl") {
			writer.write_opcode(ByteCode::JL);
			writer.write_int(std::stoi(arg));
		} else if (op == "jge") {
			writer.write_opcode(ByteCode::JGE);
			writer.write_int(std::stoi(arg));
		} else if (op == "jle") {
			writer.write_opcode(ByteCode::JLE);
			writer.write_int(std::stoi(arg));
			
		//Other
		} else if (op == "exit") {
			writer.write_opcode(ByteCode::EXIT);
		} else if (op == "sleep") {
			writer.write_opcode(ByteCode::SLEEP);
			writer.write_int(std::stoi(arg));
		} else if (op == "new_thread") {
			writer.write_opcode(ByteCode::NEW_THREAD);
			writer.write_int(std::stoi(arg));
		} else if (op == "call") {
			writer.write_opcode(ByteCode::CALL);
			writer.write_int(std::stoi(arg));
		} else if (op == "ret") {
			writer.write_opcode(ByteCode::RET);
			
		//External library
		} else if (op == "lib") {
			writer.write_opcode(ByteCode::LIB);
			auto s = arg.substr(1, arg.length()-2);
			
			std::string lib = strtok((char *)s.c_str(), ">");
			std::string func_name = strtok(NULL, ":");
			std::string type = strtok(NULL, "; ");
			std::string ret = strtok(NULL, " ");
			
			if (type == "void") {
				writer.write_opcode(0x1);
			} else if (type == "int") {
				writer.write_opcode(0x2);
			} else if (type == "dec") {
				writer.write_opcode(0x3);
			} else if (type == "str") {
				writer.write_opcode(0x4);
			}
			
			if (ret == "void") {
				writer.write_opcode(0x1);
			} else if (ret == "int") {
				writer.write_opcode(0x2);
			} else if (ret == "dec") {
				writer.write_opcode(0x3);
			} else if (ret == "str") {
				writer.write_opcode(0x4);
			}
			
			writer.write_str(lib.c_str());
			writer.write_str(func_name.c_str());
		} else if (op == "excall") {
			writer.write_opcode(ByteCode::EXCALL);
			auto s = arg.substr(1, arg.length()-2);
			writer.write_str(s.c_str());
		
		//Error
		} else {
			std::cout << "Fatal Error!" << std::endl;
			std::cout << "Invalid instruction: " << op << std::endl;
			std::exit(1);
		}
	}
}
