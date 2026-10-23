#pragma once
#include <string>
#include <utf8proc/utf8proc.h>
#include <stdexcept>

namespace utf8 {

    inline std::string str_sort_key(const std::string& s, int opt) {
        utf8proc_uint8_t* out = nullptr;
        utf8proc_map((const utf8proc_uint8_t*)s.c_str(), s.size(), &out, static_cast<utf8proc_option_t>(opt));

        std::string result = out
            ? std::string((char*)out)
            : std::string(s);

        free(out);

        return result;
    }

    inline size_t char_length(const std::string& str, size_t pos, utf8proc_int32_t& codepoint) {
        utf8proc_ssize_t len = utf8proc_iterate(
            reinterpret_cast<const utf8proc_uint8_t*>(str.data() + pos),
            str.size() - pos,
            &codepoint
        );

        if (len < 0)
            throw std::invalid_argument("Error: invalid UTF-8.");

        return static_cast<size_t>(len);
    }

    inline size_t char_count(const std::string& str) {
        size_t count = 0;
        size_t pos = 0;
        utf8proc_int32_t prev = 0;
        utf8proc_int32_t curr = 0;
        utf8proc_int32_t state = 0;

        while (pos < str.size()) {
            size_t len = char_length(str, pos, curr);

            if (count == 0 ||
                utf8proc_grapheme_break_stateful(prev, curr, &state)) {
                ++count;
            }

            prev = curr;
            pos += static_cast<size_t>(len);
        }

        return count;
    }

    inline std::string substring(const std::string& str, size_t offset, size_t count) {
        size_t pos = 0;
        size_t charCount = 0;
        size_t start = str.size();
        utf8proc_int32_t prev = 0;
        utf8proc_int32_t curr = 0;
        utf8proc_int32_t state = 0;

        while (pos < str.size()) {
            utf8proc_ssize_t len = char_length(str, pos, curr);

            if (charCount == 0 || utf8proc_grapheme_break_stateful(prev, curr, &state)) {

                if (charCount == offset)
                    start = pos;

                if (charCount == offset + count)
                    return str.substr(start, pos - start);

                ++charCount;
            }

            prev = curr;
            pos += static_cast<size_t>(len);
        }

        if (offset >= charCount)
            return {};

        return str.substr(start);
    }
}