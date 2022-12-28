cmake_minimum_required(VERSION 3.14)

project(stack)

add_library(libStack STATIC src/ThreadSafeStack.cpp include/ThreadSafeStack.h)

set_target_properties(
	libStack PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


