cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS " -O3")

add_executable(
	main
	Main/src/main.cpp
	Main/src/Headers/Vector.h
	Main/src/Headers/Timer.h
)