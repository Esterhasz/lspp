#pragma once
#include <vector>
#include <filesystem>
#include "strategy/Measurer.h"

class Item;

namespace fn {

	std::vector<Item> scan_directory(std::filesystem::path&, Measurer);
}