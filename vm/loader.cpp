#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <cstring>
#include <map>

#include "loader.hh"

//Opened files
std::map<std::string, void *> open_libs;

//Handles external function calls
void excall(std::string cmd, Context *context) {
	//Parse input string
	std::string lib = "libqk";
	std::string func_name = "";
	unsigned char type = cmd[0];
	unsigned char ret = cmd[1];
	bool found = false;
	
	for (int i = 2; i<cmd.length(); i++) {
		if (cmd[i] == ';') {
			lib += ".so";
			found = true;
			continue;
		}
		
		if (found)
			func_name += cmd[i];
		else
			lib += cmd[i];
	}

	//Set up needed values
	void *handle;
	void (*func)(void *);
	int (*i_func)(void *);
	char *(*str_func)(void *);
	void *arg;
	
	//Create the input arguments
	if (type == 0x2) {
		arg = (void *)&context->int_stack.top();
	} else if (type == 0x3) {
		arg = (void *)&context->flt_stack.top();
	} else if (type == 0x4) {
		arg = (void *)&context->str_stack.top();
	}
	
	//Load the library
	if (open_libs.find(lib) != open_libs.end()) {
		handle = open_libs[lib];
	} else {
		handle = dlopen(lib.c_str(), RTLD_LAZY);
		if (!handle) {
			std::cout << "Error: Unable to load API" << std::endl;
			std::exit(1);
		}
		
		dlerror();
		
		open_libs[lib] = handle;
	}
	
	//Call and if necessary, get return type
	if (ret == 0x2) {
		i_func = (int (*)(void *))dlsym(handle, (char *)func_name.c_str());
		int x = i_func(arg);
		context->int_stack.push(x);
	} else if (ret == 0x1) {
		*(void **)(&func) = dlsym(handle, (char *)func_name.c_str());
		(*func)(arg);
	} else if (ret = 0x4) {
		str_func = (char *(*)(void *))dlsym(handle, (char *)func_name.c_str());
		char *s = str_func(arg);
		context->str_stack.push(std::string(s));
	}
}
