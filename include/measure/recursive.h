#pragma once
#include "Item.h"
#include "fn/directory_size.h"

namespace measure {
	inline uintmax_t recursive(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		namespace fs = std::filesystem;
		std::error_code e;

		if (type == fs::file_type::directory)
			return fn::directory_size(entry.path());

		std::error_code e;
		auto size = entry.file_size(e);

		if (!e)
			return size;

		return 0;
	}
}