#pragma once
#include <filesystem>

namespace measure {
	inline uintmax_t shallow(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		std::error_code e;
		return entry.file_size(e);
	}
}