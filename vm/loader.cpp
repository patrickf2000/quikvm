#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <cstring>

#include "loader.hh"

void excall(std::string cmd, Context *context) {
	/*int pos = cmd.find(">");
	auto lib = "libqk" + cmd.substr(0, pos) + ".so";
	auto func_name = cmd.substr(pos+1);
	
	std::string type = "NULL";
	std::string ret = "NULL";
	
	int dpos = func_name.find(":");
	if (dpos != std::string::npos) {
		type = func_name.substr(dpos+1);
		func_name = cmd.substr(pos+1, dpos);
	}*/
	
	std::string lib = "libqk";
	lib += std::string(strtok((char *)cmd.c_str(), ">"));
	lib += ".so";
	
	std::string func_name = strtok(NULL, ":");
	std::string type = strtok(NULL, "; ");
	std::string ret = strtok(NULL, " ");

	
	void *handle;
	void (*func)(void *);
	int (*i_func)(void *);
	void *arg;
	
	if (type == "int") {
		arg = (void *)&context->int_stack.top();
	} else if (type == "dec") {
		arg = (void *)&context->flt_stack.top();
	}
	
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	if (!handle) {
		std::cout << "Error: Unable to load API" << std::endl;
		std::exit(1);
	}
	
	dlerror();
	
	if (ret == "int") {
		i_func = (int (*)(void *))dlsym(handle, (char *)func_name.c_str());
		int x = i_func(arg);
		context->int_stack.push(x);
	} else if (ret == "void") {
		*(void **)(&func) = dlsym(handle, (char *)func_name.c_str());
		(*func)(arg);
	}
	
	dlclose(handle);
}
