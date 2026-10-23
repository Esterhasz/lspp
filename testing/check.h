#pragma once
#include <iostream>
#include <string_view>

namespace test
{
    inline int passed = 0;
    inline int failed = 0;

    static inline void check(bool condition, std::string_view expression, std::string_view file, int line)
    {
        if (condition)
        {
            ++passed;
            std::cout << "[+] " << expression << '\n';
        }
        else
        {
            ++failed;
            std::cout << "[-] " << file << ':' << line
                << ": " << expression << '\n';
        }
    }
}

#define CHECK(expr) ::test::check(static_cast<bool>(expr), #expr, __FILE__, __LINE__)