#include <iostream>

#include "vm.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input specified!" << std::endl;
		return 1;
	}
	
	load(argv[1]);
	run(0);
	
	return 0;
}
