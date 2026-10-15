#pragma once
#include "Item.h"

namespace predicate {
	inline bool by_time(const Item& a, const Item& b) {
		return a.last_write() > b.last_write();
	}
}