#pragma once
#include "Item.h"
#include <optional>

namespace priority {

	inline std::optional<bool> directories(const Item& a, const Item& b) {

		if (a.type() != b.type()) {
			return a.type() == ItemType::directory;
		}

		return std::nullopt;
	}
}