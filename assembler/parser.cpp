#include "parser.hh"

std::string get_operand(std::string ln) {
	std::string ret = "";
	
	for (char c : ln) {
		if (c == ' ')
			break;
		ret += c;
	}
	
	return ret;
}

std::string get_arg(std::string ln) {
	std::string ret = "";
	bool found = false;
	
	for (char c : ln) {
		if (c == ' ' && !found) {
			found = true;
		} else if (found) {
			ret += c;
		}
	}
	
	return ret;
}
