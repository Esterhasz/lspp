#pragma once
#include "TypeUnion.h"
#include "Measurer.h"
#include "Prioritizer.h"
#include "Comparator.h"
#include "Predicate.h"

using lspp_config = TypeUnion<Measurer, Prioritizer, Comparator, Predicate, std::filesystem::path>;