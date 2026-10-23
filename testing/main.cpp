#include <iostream>
#include "run_tests.h"
#include "check.h"

int main() {

    std::cout << "\n";

    run_tests();

    std::cout << "\n"
        << test::passed << " passed, "
        << test::failed << " failed\n\n";

    return test::failed == 0 ? 0 : -1;
}