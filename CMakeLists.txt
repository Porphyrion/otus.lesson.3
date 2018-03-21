cmake_minimum_required(VERSION 3.2)

project(alloc)

add_executable(main main.cpp)

set_target_properties(main PROPERTIES
	CXX_STANDARD 14
	CXX_STANDART_REQUIRED YES
	COMPILE_OPTION -Wpedantic -Wall -Wextra
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
