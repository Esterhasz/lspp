#pragma once
#include <filesystem>
#include <optional>

using ItemType = std::filesystem::file_type;
using Path = std::filesystem::path;
using Entry = std::filesystem::directory_entry;
using LastWrite = std::filesystem::file_time_type;

class Item {

private:
	Path _path;
	ItemType _type;
	std::optional<uintmax_t> _size;
	LastWrite _lastWrite;
	
public:
	Item(const Path& path, ItemType type, std::optional<uintmax_t> size, LastWrite lastWrite) : 
		_size(size), 
		_path(path), 
		_type(type), 
		_lastWrite(lastWrite) {
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
	std::optional<uintmax_t> size() const {
		return _size;
	}
	LastWrite last_write() const {
		return _lastWrite;
	}
};