#pragma once
#include <filesystem>

namespace measure {
	inline uintmax_t files(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		namespace fs = std::filesystem;
		
		if (type == fs::file_type::directory)
			return 0;
		
		std::error_code e;
		auto size = entry.file_size(e);

		if (!e)
			return size;

		return 0;
	}
}