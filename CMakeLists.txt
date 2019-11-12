cmake_minimum_required(VERSION 3.0.0)
project(vm2)

set(ASM_SRC
	assembler/main.cpp
	assembler/writer.cpp
	assembler/assembler.cpp
)

set(LIBVM_SRC
	libvm/reader.cpp
	libvm/vm.cpp
	libvm/loader.cpp
)

set(VM_SRC
	vm/main.cpp
)

find_library(pthread REQUIRED)

add_compile_options(-std=c++11 -g)

include_directories(common)
include_directories(libvm)

add_library(qkvml ${LIBVM_SRC})

add_executable(qkasm ${ASM_SRC})
add_executable(qkvm ${VM_SRC})

add_library(qktest SHARED stdlib/test.c)
add_library(qkstr SHARED stdlib/str.c)
add_library(qkio SHARED stdlib/io.c)

target_link_libraries(qkvml pthread dl)
target_link_libraries(qkvm qkvml)

