#pragma once
#include <string>

namespace utf8 {
    size_t char_length(unsigned char c) {
        if ((c & 0x80) == 0x00) return 1;
        if ((c & 0xE0) == 0xC0) return 2;
        if ((c & 0xF0) == 0xE0) return 3;
        if ((c & 0xF8) == 0xF0) return 4;
        return 1;
    }

    size_t char_count(const std::string& str) {
        size_t p = 0;
        size_t count = 0;
        while (p < str.size()) {
            p += char_length(str[p]);
            ++count;
        }

        return count;
    }

    std::string substring(const std::string& str, size_t offset, size_t count) {
        size_t charCount = 0;
        size_t p = 0;

        std::string result{};

        for (size_t i = 0; i < offset; ++i) {
            p += char_length(str[p]);
        }

        for (; p < str.size() && charCount < count; ) {
            charCount++;
            char c = str[p];

            size_t len = char_length(str[p]);

            result.append(str, p, len);
            p += len;
        }

        return result;
    }
}