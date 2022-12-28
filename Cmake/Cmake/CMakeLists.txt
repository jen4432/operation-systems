cmake_minimum_required(VERSION 3.14)

project(Find_Prime)

add_subdirectory(stack)
add_subdirectory(Solver)

add_executable(Find_Prime main.cpp)

set_target_properties(
	Find_Prime PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(
	Find_Prime
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../libStack
	${CMAKE_CURRENT_SOURCE_DIR}/../libSolver
)

target_link_libraries(Find_Prime libSolver libStack)