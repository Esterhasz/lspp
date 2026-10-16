#pragma once
#include "Item.h"
#include <optional>

namespace priority {

	inline std::optional<bool> none(const Item& a, const Item& b) {
		return std::nullopt;
	}
}