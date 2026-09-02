#pragma once
#include <filesystem>

namespace measure {
	inline uintmax_t shallow(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		return entry.file_size();
	}
}