cmake_minimum_required(VERSION 3.14)

project(stack)

add_library(libSolver STATIC Solver.cpp Solver.h)

set_target_properties(
	libSolver PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)