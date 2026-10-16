#pragma once
#include "Item.h"

namespace predicate {
	inline bool by_size(const Item& a, const Item& b) {
		return a.size() > b.size();
	}
}