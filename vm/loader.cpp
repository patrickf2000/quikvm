#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

#include "loader.hh"

void excall(std::string cmd) {
	int pos = cmd.find(">");
	auto lib = "libqk" + cmd.substr(0, pos) + ".so";
	auto func_name = cmd.substr(pos+1);
	
	void *handle;
	void (*func)(void);
	
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	if (!handle) {
		std::cout << "Error: Unable to load API" << std::endl;
		std::exit(1);
	}
	
	dlerror();
	
	*(void **)(&func) = dlsym(handle, func_name.c_str());
	(*func)();
	
	dlclose(handle);
}
