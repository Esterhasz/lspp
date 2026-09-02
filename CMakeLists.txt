cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("include")

project ("lspp" VERSION 1.2.0)

file (GLOB_RECURSE SRC_FILES 
	"include/*.h"
	"include/*.hpp"
	"src/*.cpp")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

add_executable(lspp
    ${SRC_FILES}
    ".lib/utf8proc.c"
)

target_include_directories(lspp PRIVATE ".lib/")
target_compile_definitions(lspp PRIVATE UTF8PROC_STATIC)