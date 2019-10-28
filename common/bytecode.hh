#pragma once

enum ByteCode {
	//General
	EXIT = 0x10,
	
	//Integer
	I_LOAD = 0x20,
	I_PRINT = 0x21,
	
	//Double (floating point)
	D_LOAD = 0x30,
	D_PRINT = 0x31,
};
