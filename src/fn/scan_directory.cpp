#include "fn/scan_directory.h"
#include "Item.h"

namespace fn {
	std::vector<Item> scan_directory(Path path, Measurer measurer) {
		namespace fs = std::filesystem;

		std::vector<Item> content{};
		content.reserve(16);

		uintmax_t itemCount = 0;

		std::error_code ec;

		for (auto& entry : fs::directory_iterator(
			path, 
			fs::directory_options::skip_permission_denied, 
			ec)) {

			auto type = entry.status().type();

			content.emplace_back(entry.path(), type, measurer(entry, type));
		}

		return content;
	}
}