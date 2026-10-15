#pragma once
#include <charconv>
#include <stdexcept>
#include <string_view>

namespace fn {
    std::size_t parse_size(std::string_view str) {
        std::size_t value{};

        auto [ptr, ec] = std::from_chars(
            str.data(),
            str.data() + str.size(),
            value
        );

        if (ec != std::errc{} || ptr != str.data() + str.size()) {
            throw std::invalid_argument("Invalid number: " + std::string(str));
        }

        return value;
    }
}