#pragma once
#include "by_name.h"

static constexpr utf8proc_option_t OPTIONS_CASE_SENSITIVE = (utf8proc_option_t)(
	UTF8PROC_STABLE | 
	UTF8PROC_COMPOSE | 
	UTF8PROC_CASEFOLD);

namespace predicate {
	inline bool by_name_cs(const Item& a, const Item& b) {
		return by_name(a, b, OPTIONS_CASE_SENSITIVE);
	}
}