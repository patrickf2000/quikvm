#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <cstring>

#include "loader.hh"

//Handles external function calls
void excall(std::string cmd, Context *context) {
	//Parse input string
	std::string lib = "libqk";
	lib += std::string(strtok((char *)cmd.c_str(), ">"));
	lib += ".so";
	
	std::string func_name = strtok(NULL, ":");
	std::string type = strtok(NULL, "; ");
	std::string ret = strtok(NULL, " ");

	//Set up needed values
	void *handle;
	void (*func)(void *);
	int (*i_func)(void *);
	void *arg;
	
	//Create the input arguments
	if (type == "int") {
		arg = (void *)&context->int_stack.top();
	} else if (type == "dec") {
		arg = (void *)&context->flt_stack.top();
	}
	
	//Load the library
	handle = dlopen(lib.c_str(), RTLD_LAZY);
	if (!handle) {
		std::cout << "Error: Unable to load API" << std::endl;
		std::exit(1);
	}
	
	dlerror();
	
	//Call and if necessary, get return type
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
