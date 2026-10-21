#include "fn/directory_size.h"

uintmax_t fn::directory_size(const std::filesystem::path p) {
	namespace fs = std::filesystem;

	std::error_code ec;
	uintmax_t size = 0;

	auto it = fs::recursive_directory_iterator(
		p,
		fs::directory_options::skip_permission_denied,
		ec);

	fs::recursive_directory_iterator end;

	for (; it != end; it.increment(ec)) {
		if (ec) {
			ec.clear();
			continue;
		}

		if (it->is_regular_file(ec)) {
			
			uintmax_t fileSize = it->file_size(ec);

			if (ec) {
				ec.clear();
				continue;
			}

			size += fileSize;
		}
	}

	return size;
}