#pragma once
#include <filesystem>
#include <optional>

namespace measure {
	inline std::optional<uintmax_t> shallow(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		std::error_code e;
		auto size = entry.file_size(e);

		if (!e)
			return size;

		return std::nullopt;
	}
}