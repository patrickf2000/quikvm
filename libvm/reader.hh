#pragma once

#include <fstream>
#include <string>

class BinReader {
public:
	explicit BinReader(const char *path);
	bool is_eof();
	unsigned char read_opcode();
	int read_int();
	double read_double();
	std::string read_str();
	void close();
private:
	std::ifstream reader;
};
