#include "assembler.hh"

std::map<std::string, int> symbols;

void pass1(std::vector<std::string> *contents) {
	std::vector<std::string> ret;

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		if (op == "lbl") {
			symbols.insert(std::pair<std::string, int>(arg, i));
			ln = op + " " + std::to_string(i);
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}

	for (int i = 0; i<contents->size(); i++) {
		auto ln = contents->at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);

		if (op == "jmp" || op == "je") {
			ln = op + " ";
			ln += std::to_string(symbols.at(arg));
		}
		
		contents->insert(contents->begin()+i+1, ln);
		contents->erase(contents->begin()+i);
	}
}
