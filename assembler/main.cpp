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
	
	//Check command line arguments
	bool p1 = false;
	
	for (int i = 1; i<argc; i++) {
		if (std::string(argv[i]) == "-p1") {
			p1 = true;
		}
	}
	
	//Load the file
	auto input = std::string(argv[1]);
	std::string ln = "";
	
	std::ifstream reader(input.c_str());
	if (!reader.is_open()) {
		std::cout << "Fatal: Unable to open input file." << std::endl;
		return 1;
	}
	
	std::vector<std::string> contents;
	
	//Load and cleanup each line
	while (std::getline(reader, ln)) {
		ln.erase(0, ln.find_first_not_of(" \t"));
		ln.erase(ln.find_last_not_of(" \t")+1);
		
		if (ln[0] == ';') continue;
		if (ln.length() == 0) continue;
		
		contents.push_back(ln);
	}
	
	reader.close();
	
	//Assemble
	pass1(&contents, p1);
	pass2(&contents, input);
	
	return 0;
}
