#pragma once
#include "Item.h"
#include "strategy/Prioritizer.h"
#include "strategy/Predicate.h"

namespace compare {
	inline bool normal(const Item& a, const Item& b, Prioritizer prioritize, Predicate compare) {
		auto result = prioritize(a, b);

		if (result == std::nullopt)
			return compare(a, b);

		return result.value();
	}
}