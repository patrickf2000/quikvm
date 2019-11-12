#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <cstring>
#include <map>

#include "loader.hh"

//Opened files
std::map<std::string, Func> open_libs;

//Loads needed libraries
void lib(std::string cmd) {
	//Parse input string
	std::string lib = "lib";
	std::string func_name = "";
	unsigned char type = cmd[0];
	unsigned char ret = cmd[1];
	bool found = false;
	void *handle;
	
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
	
	//Load the library
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	if (!handle) {
		std::cout << "Error: Unable to load API" << std::endl;
		std::exit(1);
	}
	
	dlerror();
	
	Func f;
	f.handle = handle;
	f.lib = lib;
	f.func_name = func_name;
	f.type = type;
	f.ret = ret;
	open_libs[func_name] = f;
}

//Handles external function calls
void excall(std::string name, Context *context) {
	Func f = open_libs[name];

	//Set up needed values
	void (*func)(void *);
	int (*i_func)(void *);
	char *(*str_func)(void *);
	void *arg;
	
	//Create the input arguments
	if (f.type == 0x2) {
		arg = (void *)&context->int_stack.top();
	} else if (f.type == 0x3) {
		arg = (void *)&context->flt_stack.top();
	} else if (f.type == 0x4) {
		arg = (void *)&context->str_stack.top();
	}
	
	//Call and if necessary, get return type
	if (f.ret == 0x2) {
		i_func = (int (*)(void *))dlsym(f.handle, (char *)f.func_name.c_str());
		int x = i_func(arg);
		context->int_stack.push(x);
	} else if (f.ret == 0x1) {
		*(void **)(&func) = dlsym(f.handle, (char *)f.func_name.c_str());
		(*func)(arg);
	} else if (f.ret = 0x4) {
		str_func = (char *(*)(void *))dlsym(f.handle, (char *)f.func_name.c_str());
		char *s = str_func(arg);
		context->str_stack.push(std::string(s));
	}
}
