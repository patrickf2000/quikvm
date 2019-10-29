#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "assembler.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input file specified" << std::endl;
		return 1;
	}
	
	auto input = std::string(argv[1]);
	std::string ln = "";
	
	std::ifstream reader(input.c_str());
	if (!reader.is_open()) {
		std::cout << "Fatal: Unable to open input file." << std::endl;
		return 1;
	}
	
	std::vector<std::string> contents;
	
	while (std::getline(reader, ln)) {
		contents.push_back(ln);
	}
	
	reader.close();
	
	pass1(&contents);
	pass2(&contents, input);
	
	return 0;
}
