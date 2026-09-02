cmake_minimum_required(VERSION 3.20)

project(lspp VERSION 1.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

include_directories("include")

file(GLOB_RECURSE SRC_FILES
    "include/*.h"
    "include/*.hpp"
    "src/*.cpp"
)

add_executable(lspp
    ${SRC_FILES}
    ".lib/utf8proc.c"
)

target_include_directories(lspp PRIVATE ".lib/")
target_compile_definitions(lspp PRIVATE UTF8PROC_STATIC)

option(LSPP_BUILD_TESTS "Build tests" OFF)

if(LSPP_BUILD_TESTS)
    add_subdirectory(tests)
endif()