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

    uint8_t sizeLengthReserve = 7;
    uint8_t nameLengthReserve = 24;
    uint8_t dateLengthReserve = 10;
    uint8_t spacing = 4;

    const std::string splitter = "~";
    
    std::vector<Column> columns = {
        Column::Line, Column::Name, Column::Size
    };

    size_t lineLimit = 0;
};