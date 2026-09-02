include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)
file(GLOB_RECURSE SRC_FILES
    "../include/*.h"
    "../include/*.hpp"
    "../src/fn/*.cpp"
)

add_executable(lspp_tests 
    ${SRC_FILES}
    "../.lib/utf8proc.c"
    reverse_test.cpp
)

    
target_include_directories(lspp_tests PRIVATE "../.lib/")
target_compile_definitions(lspp_tests PRIVATE UTF8PROC_STATIC)

target_link_libraries(lspp_tests PRIVATE
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

enable_testing()
catch_discover_tests(lspp_tests)