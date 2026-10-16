#pragma once
#include <filesystem>
#include <optional>

namespace measure {
	inline std::optional<uintmax_t> none(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		return std::nullopt;
	}
}