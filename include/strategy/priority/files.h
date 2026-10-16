#pragma once
#include "Item.h"
#include <optional>

namespace priority {

	inline std::optional<bool> files(const Item& a, const Item& b) {

		if (a.type() != b.type()) {
			return b.type() == ItemType::directory;
		}

		return std::nullopt;
	}
}