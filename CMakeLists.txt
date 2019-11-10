cmake_minimum_required(VERSION 3.0.0)
project(vm2)

set(ASM_SRC
	assembler/main.cpp
	assembler/writer.cpp
	assembler/assembler.cpp
)

set(VM_SRC
	vm/main.cpp
	vm/reader.cpp
	vm/vm.cpp
	vm/loader.cpp
)

find_library(pthread REQUIRED)

add_compile_options(-std=c++11 -g)
include_directories(common)

add_executable(qkasm ${ASM_SRC})
add_executable(qkvm ${VM_SRC})

add_library(qktest SHARED stdlib/test.c)
add_library(qkstr SHARED stdlib/str.c)
add_library(qkio SHARED stdlib/io.c)

target_link_libraries(qkvm pthread dl)

