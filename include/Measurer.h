#pragma once
#include <filesystem>

using Measurer = uintmax_t(*)(const std::filesystem::directory_entry&, std::filesystem::file_type);