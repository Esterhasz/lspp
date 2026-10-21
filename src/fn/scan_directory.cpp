#include "fn/scan_directory.h"
#include "Item.h"

namespace fn {
	std::vector<Item> scan_directory(std::filesystem::path& p, Measurer measurer) {
		namespace fs = std::filesystem;

		std::vector<Item> content{};
		content.reserve(16);

		uintmax_t itemCount = 0;

		std::error_code ec;

		for (auto& entry : fs::directory_iterator(
			p, 
			fs::directory_options::skip_permission_denied, 
			ec)) {

			auto type = entry.status().type();

			content.emplace_back(entry.path(), type, measurer(entry, type), entry.last_write_time());
		}

		return content;
	}
}