#pragma once
#include <filesystem>

namespace measure {
	inline uintmax_t none(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		return 0;
	}
}