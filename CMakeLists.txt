cmake_minimum_required(VERSION 3.0.0)
project(vm2)

set(ASM_SRC
	assembler/main.cpp
	assembler/parser.cpp
	assembler/writer.cpp
)

set(VM_SRC
	vm/main.cpp
	vm/reader.cpp
)

add_compile_options(-std=c++11)
include_directories(common)

add_executable(asm ${ASM_SRC})
add_executable(vm ${VM_SRC})

