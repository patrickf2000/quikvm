#include <iostream>
#include <cstdlib>

#include <bytecode.hh>

#include "reader.hh"

//Open our input stream
BinReader::BinReader(const char *path) {
	reader = std::ifstream(path, std::ios::binary);
	
	if (!reader.is_open()) {
		std::cout << "Error: Unable to open input!" << std::endl;
		std::cout << "PATH: " << path << std::endl;
		std::exit(1);
	}
	
	//Check the header
	char head[5];
	reader.read(head, 5);
	
	unsigned char header[] = {'Q', 'U', 'I', 'C', 'K'};
	
	for (int i = 0; i<5; i++) {
		if ((unsigned char)head[i] != header[i]) {
			std::cout << "Error: Invalid input file!" << std::endl;
			std::cout << "The header does not match." << std::endl;
			std::exit(1);
		}
	}	
}

//Returns whether we are at the end of our file
bool BinReader::is_eof() {
	if (reader) {
		return false;
	}
	return true;
}

//Read an opcode
unsigned char BinReader::read_opcode() {
	unsigned char op;
	reader.read((char *)&op, sizeof(unsigned char));
	return op;
}

//Read an integer
int BinReader::read_int() {
	int arg;
	reader.read((char *)&arg, sizeof(int));
	return arg;
}

//Read a double
double BinReader::read_double() {
	double arg;
	reader.read((char *)&arg, sizeof(double));
	return arg;
}

//Read a string
std::string BinReader::read_str() {
	int len = read_int();
	char str[len];
	reader.read((char *)str, sizeof(char)*len);
	str[len] = '\0';
	return std::string(str);
}

//Close everything
void BinReader::close() {
	reader.close();
}
