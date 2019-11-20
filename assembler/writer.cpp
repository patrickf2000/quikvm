#include <cstring>
#include <iostream>

#include "writer.hh"

//Set up the writer
BinWriter::BinWriter(std::string path) {
	writer = std::ofstream(path.c_str(), std::ios::binary);
	
	unsigned char header[] = {'Q', 'U', 'I', 'C', 'K'};
	for (int i = 0; i<5; i++) {
		write_opcode(header[i]);
	}
}

//Write an opcode
void BinWriter::write_opcode(unsigned char op) {
	writer.write((const char *)&op, sizeof(unsigned char));
}

//Write an integer
void BinWriter::write_int(int arg) {
	writer.write((const char *)&arg, sizeof(int));
}

//Write a double
void BinWriter::write_double(double arg) {
	writer.write((const char *)&arg, sizeof(double));
}

//Write a string
void BinWriter::write_str(const char *str) {
	int size = strlen(str);
	write_int(size);
	writer.write((const char *)str, sizeof(char)*size);
}

//Save the file
void BinWriter::write() {
	writer.close();
}


