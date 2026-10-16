#pragma once

enum Column {
	Name = 1, 
	Date = 1 << 1,
	Size = 1 << 2,
	Line = 1 << 3,
};

inline Column operator|(Column a, Column b) {
	return static_cast<Column>(static_cast<int>(a) | static_cast<int>(b));
}

struct print_config {
    static constexpr size_t NAME_LENGTH_RESERVE = 24;
    static constexpr size_t NAME_LEFT_PART = 11;
    static constexpr size_t NAME_RIGHT_PART = 10;

    static constexpr size_t DATE_LENGTH_RESERVE = 10;
    
    static constexpr size_t SPACES = 4;

    std::vector<Column> columns = { Column::Line, Column::Name, Column::Size };
    size_t lineLimit = 0;
};