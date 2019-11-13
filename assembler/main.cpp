#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "loader.hh"
#include "assembler.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input file specified" << std::endl;
		return 1;
	}
	
	//Check command line arguments
	bool p1 = false;
	std::vector<char *> files;
	
	for (int i = 1; i<argc; i++) {
		if (std::string(argv[i]) == "-p1") {
			p1 = true;
		} else {
			files.push_back(argv[i]);
		}
	}
	
	//Load the file
	auto contents = load_file(argv[1]);
	
	//Assemble
	pass1(&contents, p1);
	pass2(&contents, argv[1]);
	
	return 0;
}
