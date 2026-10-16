#pragma once
#include <optional>
#include "Item.h"

using Prioritizer = std::optional<bool>(*)(const Item&, const Item&);