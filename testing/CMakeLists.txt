file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "../include/*.h"
    "../include/*.hpp"
    "../src/*.cpp"
    "./*.cpp"
    "./*.h"
)

list(FILTER SRC_FILES EXCLUDE REGEX "[/\\\\]lspp\\.cpp$")

add_executable(lspp_tests
    ${SRC_FILES}
    "../.lib/utf8proc/utf8proc.c"
    "../.lib/whereami/whereami.c"
)


target_include_directories(lspp_tests PRIVATE
    ../include
    ../.lib
)

target_include_directories(lspp_tests PRIVATE ".lib/")
target_compile_definitions(lspp_tests PRIVATE UTF8PROC_STATIC)

enable_testing()

add_test(NAME lspp_tests COMMAND lspp_tests)

add_custom_target(run_tests ALL
    COMMAND $<TARGET_FILE:lspp_tests>
    DEPENDS lspp_tests
    USES_TERMINAL
    VERBATIM
)