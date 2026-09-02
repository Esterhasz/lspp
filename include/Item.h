#pragma once
#include <filesystem>

using ItemType = std::filesystem::file_type;
using Path = std::filesystem::path;
using Entry = std::filesystem::directory_entry;

class Item {
	Path _path;
	ItemType _type;
	uintmax_t _size;
	
public:
	Item(Path absolutePath, ItemType type, uintmax_t size) : 
		_size(size), 
		_path(absolutePath), 
		_type(type) {
	}

	const Path& path() const {
		return _path;
	}
	ItemType type() const {
		return _type;
	}
	Path filename() const {
		return path().filename();
	}
	uintmax_t size() const {
		return _size;
	}
};