#pragma once

#include <fstream>

class BinWriter {
public:
	explicit BinWriter(std::string path);
	void write_opcode(unsigned char op);
	void write_int(int arg);
	void write_double(double arg);
	void write_str(const char *str);
	void write();
private:
	std::ofstream writer;
};
