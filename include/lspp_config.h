#pragma once
#include "strategy/Measurer.h"
#include "strategy/Prioritizer.h"
#include "strategy/Comparator.h"
#include "strategy/Predicate.h"
#include "strategy/measure/all.h"
#include "strategy/priority/all.h"
#include "strategy/compare/all.h"
#include "strategy/predicate/all.h"

#include "print_config.h"

struct lspp_config {

	using Path = std::filesystem::path;

	static constexpr char CONFIG_FILENAME[] = "config.txt";
	static constexpr uint8_t V_CAP = 16;

	Measurer	measurer	= measure::files;
	Prioritizer prioritizer = priority::directories;
	Comparator  comparator	= compare::normal;
	Predicate	predicate	= predicate::by_name_ci;
	
	Path path = std::filesystem::current_path();
	Path executableDir{};

	print_config print{};

	void set(Measurer value)	{ measurer		= std::move(value); }
	void set(Prioritizer value) { prioritizer	= std::move(value); }
	void set(Comparator value)	{ comparator	= std::move(value); }
	void set(Predicate value)	{ predicate		= std::move(value); }
	void set(Path value)		{ path			= std::move(value); }
};