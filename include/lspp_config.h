#pragma once
#include "Measurer.h"
#include "Prioritizer.h"
#include "Comparator.h"
#include "Predicate.h"
#include "print_config.h"
#include "measure/all.h"
#include "priority/all.h"
#include "compare/all.h"
#include "predicate/all.h"

struct lspp_config {

	using Path = std::filesystem::path;

	Measurer	measurer	= measure::files;
	Prioritizer prioritizer = priority::directories;
	Comparator  comparator	= compare::normal;
	Predicate	predicate	= predicate::by_name_ci;
	
	Path path = std::filesystem::current_path();
	Path executablePath{};

	print_config print{};

	void set(Measurer value)	{ measurer		= std::move(value); }
	void set(Prioritizer value) { prioritizer	= std::move(value); }
	void set(Comparator value)	{ comparator	= std::move(value); }
	void set(Predicate value)	{ predicate		= std::move(value); }
	void set(Path value)		{ path			= std::move(value); }
};