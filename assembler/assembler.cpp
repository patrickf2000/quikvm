#include "assembler.hh"

std::map<std::string, int> symbols;

//TODO: See if we can clear this up, this is a lot of looping
std::vector<std::string> pass1(std::vector<std::string> contents) {
	std::vector<std::string> ret;

	for (int i = 0; i<contents.size(); i++) {
		auto ln = contents.at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);
		
		if (op == "lbl") {
			symbols.insert(std::pair<std::string, int>(arg, i));
			ln = op + " " + std::to_string(i);
		}
		
		ret.push_back(ln);
	}
	
	contents.clear();
	contents = ret;
	ret.clear();

	for (int i = 0; i<contents.size(); i++) {
		auto ln = contents.at(i);
		auto pos = ln.find_first_of(" ");
		auto op = ln.substr(0, pos);
		auto arg = ln.substr(pos+1, ln.length()-1);

		if (op == "jmp") {
			ln = op + " ";
			ln += std::to_string(symbols.at(arg));
		}
		
		ret.push_back(ln);
	}
	
	return ret;
}
