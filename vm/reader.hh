#pragma once

#include <fstream>

class BinReader {
public:
	explicit BinReader(const char *path);
	bool is_eof();
	unsigned char read_opcode();
	int read_int();
	double read_double();
	void close();
private:
	std::ifstream reader;
};
