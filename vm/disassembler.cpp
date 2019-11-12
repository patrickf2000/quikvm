#include <iostream>
#include <fstream>

#include <vm.hh>
#include <bytecode.hh>

#include "disassembler.hh"

std::string trans_byte(unsigned char opcode) {
	switch (opcode) {
		case ByteCode::EXIT: return "exit";
		case ByteCode::LBL: return "lbl";
		case ByteCode::SLEEP: return "sleep";
		case ByteCode::START: return "start";
		
		case ByteCode::CALL: return "call";
		case ByteCode::RET: return "ret";
		case ByteCode::LIB: return "lib";
		case ByteCode::EXCALL: return "excall";
		
		case ByteCode::I_LOAD: return "i_load";
		case ByteCode::I_STORE: return "i_store";
		case ByteCode::I_VAR: return "i_var";
		case ByteCode::I_LOAD_VAR: return "i_load_var";
		case ByteCode::I_ADD: return "i_add";
		case ByteCode::I_SUB: return "i_sub";
		case ByteCode::I_MUL: return "i_mul";
		case ByteCode::I_DIV: return "i_div";
		case ByteCode::I_MOD: return "i_mod";
		case ByteCode::I_PRINT: return "i_print";
		case ByteCode::I_INPUT: return "i_input";
		case ByteCode::I_POP: return "i_pop";
		case ByteCode::I_ARRAY: return "i_array";
		
		case ByteCode::D_LOAD: return "d_load";
		case ByteCode::D_STORE: return "d_store";
		case ByteCode::D_VAR: return "d_var";
		case ByteCode::D_LOAD_VAR: return "d_load_var";
		case ByteCode::D_ADD: return "d_add";
		case ByteCode::D_SUB: return "d_sub";
		case ByteCode::D_MUL: return "d_mul";
		case ByteCode::D_DIV: return "d_div";
		case ByteCode::D_PRINT: return "d_print";
		case ByteCode::D_INPUT: return "d_input";
		case ByteCode::D_POP: return "d_pop";
		
		case ByteCode::S_LOAD: return "s_load";
		case ByteCode::S_PRINT: return "s_print";
		case ByteCode::S_POP: return "s_pop";
		
		case ByteCode::I_CMP: return "i_cmp";
		case ByteCode::D_CMP: return "d_cmp";
		
		case ByteCode::JMP: return "jmp";
		case ByteCode::JE: return "je";
		case ByteCode::JNE: return "jne";
		case ByteCode::JG: return "jg";
		case ByteCode::JL: return "jl";
		case ByteCode::JGE: return "jge";
		case ByteCode::JLE: return "jle";
		
		case ByteCode::NEW_THREAD: return "new_thread";
	}
	
	return "";
}

void disassemble(const char *path) {
	std::cout << "DISASSEMBLY" << std::endl;
	std::cout << "PATH: " << path << std::endl;
	std::cout << std::endl;
	
	load(path);
	
	for (auto instr : instructions) {
		std::cout << trans_byte(instr.opcode) << " ";
		
		if (int_codes.find(instr.opcode) != int_codes.end()) {
			std::cout << instr.i_arg;
		} else if (instr.opcode == ByteCode::D_LOAD) {
			std::cout << instr.d_arg;
		} else if (instr.opcode == ByteCode::S_LOAD || instr.opcode == ByteCode::EXCALL) {
			std::cout << "\"" << instr.s_arg << "\"";
		}
		
		std::cout << std::endl;
	}
}
