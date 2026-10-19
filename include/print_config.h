#pragma once
#include <vector>
#include <cstddef>

enum Column {
    Name = 1,
    Date = 1 << 1,
    Size = 1 << 2,
    Line = 1 << 3,
};

inline Column operator|(Column a, Column b) {
    return static_cast<Column>(
        static_cast<int>(a) | static_cast<int>(b)
        );
}

struct print_config {

    size_t sizeLengthReserve = 7;
    size_t nameLengthReserve = 24;
    size_t dateLengthReserve = 10;
    size_t spacing = 4;

    std::vector<Column> columns = {
        Column::Line, Column::Name, Column::Size
    };

    size_t lineLimit = 0;
};