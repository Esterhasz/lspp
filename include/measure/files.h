#pragma once
#include <filesystem>

namespace measure {
	inline uintmax_t files(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		namespace fs = std::filesystem;
		
		return type != fs::file_type::directory
			? entry.file_size()
			: 0;
	}
}