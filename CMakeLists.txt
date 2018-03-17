cmake_minimum_required(VERSION 3.5)
project(RandomNumberGeneration)

set (CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(RandomNumberGeneration	${SOURCES})
add_custom_target(run
	COMMAND RandomNumberGeneration
)
