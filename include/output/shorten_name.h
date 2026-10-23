#pragma once
#include "utf8.h"
#include <string>

inline std::string shorten_name(const std::string& str, size_t reserve, const std::string& splitter) {
    const auto splitSize = splitter.size();

    const size_t left = (reserve - splitSize + 1) / 2;
    const size_t right = (reserve - splitSize) / 2;
    const size_t length = utf8::char_count(str);

    std::string result;
    result += utf8::substring(str, 0, left);
    result += splitter;
    result += utf8::substring(str, length - right, right);

    return result;
}