#include <iostream>
#include <time.h>
#include <chrono>

#include "vm.hh"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Fatal: No input specified!" << std::endl;
		return 1;
	}
	
	bool t_monitor = false;
	
	for (int i = 1; i<argc; i++) {
		if (std::string(argv[i]) == "-t" || std::string(argv[i]) == "--time") {
			t_monitor = true;
		}
	}
	
	auto start = std::chrono::steady_clock::now();
	
	load(argv[1]);
	run_start();
	
	if (t_monitor) {
		auto end = std::chrono::steady_clock::now();
		auto diff = end - start;
		auto elapsed = std::chrono::duration <double, std::milli> (diff).count();
		
		std::cout << std::endl;
		std::cout << "Program execution time: " << std::endl;
		std::cout << elapsed << " ms" << std::endl;
		std::cout << (elapsed/1000) << " secs" << std::endl;
	}
	
	return 0;
}
