#pragma once
#include <vector>
#include "Item.h"
#include "print_config.h"

namespace output {
	void print_content(const std::vector<Item>&, const print_config&);
}