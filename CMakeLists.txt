cmake_minimum_required(VERSION 3.0.0)
project(vm2)

set(ASM_SRC
	assembler/main.cpp
	assembler/writer.cpp
	assembler/assembler.cpp
	assembler/loader.cpp
)

set(LIBVM_SRC
	libvm/reader.cpp
	libvm/vm.cpp
	libvm/loader.cpp
)

set(LIBBACK_SRC
	libbackend/program.c
	libbackend/str.c
	libbackend/vars.c
	libbackend/math.c
)

set(VM_SRC
	vm/main.cpp
	vm/disassembler.cpp
)

find_library(pthread REQUIRED)

add_compile_options(-std=c++11 -g)

include_directories(common)
include_directories(libvm)
include_directories(libbackend)

add_library(qkvml ${LIBVM_SRC})
add_library(qkbackend SHARED ${LIBBACK_SRC})

add_executable(qkasm ${ASM_SRC})
add_executable(qkvm ${VM_SRC})

#Build the test files (for the backend library)
add_executable(qktest1 libbackend/test/test1.c)
add_executable(qktest2 libbackend/test/test2.c)

#Build the API libraries
add_library(qktest SHARED stdlib/test.c)
add_library(qkstr SHARED stdlib/str.c)
add_library(qkio SHARED stdlib/io.c)

#Link everything
target_link_libraries(qkvml pthread dl)
target_link_libraries(qkvm qkvml)

target_link_libraries(qktest1 qkbackend)
target_link_libraries(qktest2 qkbackend)

