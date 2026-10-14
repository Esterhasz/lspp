#pragma once

enum Column {
	Name	= 1, 
	Date	= 1 << 1,
	Size	= 1 << 2,
	Number	= 1 << 3,
};

inline Column operator|(Column a, Column b) {
	return static_cast<Column>(static_cast<int>(a) | static_cast<int>(b));
}

struct print_config {
	Column columns;
	std::size_t lineLimit;

	print_config(Column columns, std::size_t lines) : 
		columns(columns), 
		lineLimit(lines) {
	}
};