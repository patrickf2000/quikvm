#include <fstream>
#include <iostream>

#include "loader.hh"

std::vector<std::string> load_file(const char *path) {
	std::vector<std::string> contents;
	std::string ln = "";
	
	std::ifstream reader(path);
	if (!reader.is_open()) {
		std::cout << "Fatal: Unable to open input file." << std::endl;
		return contents;
	}
	
	//Load and cleanup each line
	while (std::getline(reader, ln)) {
		ln.erase(0, ln.find_first_not_of(" \t"));
		ln.erase(ln.find_last_not_of(" \t")+1);
		
		if (ln[0] == ';') continue;
		if (ln.length() == 0) continue;
		
		contents.push_back(ln);
	}
	
	reader.close();
	
	return contents;
}

std::vector<std::string> load_multiple(std::vector<char *> *paths) {
	std::vector<std::string> contents;
	
	for (int i = 0; i<paths->size(); i++) {
		auto p = paths->at(i);
		
		auto cts = load_file(p);
		for (auto l : cts) {
			contents.push_back(l);
		}
	}
	
	return contents;
}
