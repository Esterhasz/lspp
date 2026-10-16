#pragma once
#include <filesystem>
#include <optional>

using Measurer = std::optional<uintmax_t>(*)(const std::filesystem::directory_entry&, std::filesystem::file_type);