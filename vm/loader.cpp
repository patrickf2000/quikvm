#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

#include "loader.hh"

void excall(std::string cmd, Context *context) {
	int pos = cmd.find(">");
	auto lib = "libqk" + cmd.substr(0, pos) + ".so";
	
	std::string type = "NULL";
	auto func_name = cmd.substr(pos+1);
	
	int dpos = func_name.find(":");
	if (dpos != std::string::npos) {
		type = func_name.substr(dpos+1);
		func_name = cmd.substr(pos+1, dpos);
	}
	
	void *handle;
	void (*func)(void *);
	void *arg;
	
	if (type == "int") {
		arg = (void *)&context->int_stack.top();
	}
	
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	if (!handle) {
		std::cout << "Error: Unable to load API" << std::endl;
		std::exit(1);
	}
	
	dlerror();
	
	*(void **)(&func) = dlsym(handle, func_name.c_str());
	(*func)(arg);
	
	dlclose(handle);
}
