#pragma once
#include <filesystem>

namespace fn {
	uintmax_t directory_size(const std::filesystem::path&);
}