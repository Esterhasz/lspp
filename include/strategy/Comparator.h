#pragma once
#include "Predicate.h"
#include "Prioritizer.h"
#include "Item.h"

using Comparator = bool(*)(const Item&, const Item&, Prioritizer, Predicate);