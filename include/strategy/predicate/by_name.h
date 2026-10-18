#pragma once
#include <utf8proc/utf8proc.h>
#include "utf8.h"
#include "Item.h"

namespace predicate {
	inline bool by_name(const Item& a, const Item& b, utf8proc_option_t opt) {
		return 
			utf8::str_sort_key(a.filename().u8string(), opt)
			< utf8::str_sort_key(b.filename().u8string(), opt);
	}
}