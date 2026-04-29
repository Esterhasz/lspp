cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("include")
project ("lspp" VERSION 1.0.3)

file (GLOB_RECURSE SRC_FILES 
	"include/*.h"
	"include/*.hpp"
	"src/*.cpp")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

include(FetchContent)

FetchContent_Declare(
    utf8proc
    GIT_REPOSITORY https://github.com/JuliaStrings/utf8proc.git
)

FetchContent_MakeAvailable(utf8proc)

add_executable(lspp ${SRC_FILES})
target_link_libraries(lspp PRIVATE utf8proc)