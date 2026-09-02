#pragma once
#include "Item.h"
#include "fn/directory_size.h"

namespace measure {
	inline uintmax_t recursive(const std::filesystem::directory_entry& entry, std::filesystem::file_type type) {
		std::error_code e;

		return 
			type == ItemType::directory 
			? fn::directory_size(entry.path()) 
			: entry.file_size(e);
	}
}