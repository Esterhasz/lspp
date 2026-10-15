#pragma once
#include "Measurer.h"
#include "Prioritizer.h"
#include "Comparator.h"
#include "Predicate.h"
#include "print_config.h"

struct lspp_config {
	Measurer	measurer;
	Prioritizer prioritizer;
	Comparator  comparator;
	Predicate	predicate;
	
	std::filesystem::path path;

	print_config print;

	lspp_config(
		Measurer measurer,
		Prioritizer prioritizer,
		Comparator comparator,
		Predicate predicate,
		std::filesystem::path path,
		print_config print) :

		measurer(std::move(measurer)),
		prioritizer(std::move(prioritizer)),
		comparator(std::move(comparator)),
		predicate(std::move(predicate)),
		path(std::move(path)),
		print(std::move(print)) {
	}

	void set(Measurer value) { measurer = std::move(value); }
	void set(Prioritizer value) { prioritizer = std::move(value); }
	void set(Comparator value) { comparator = std::move(value); }
	void set(Predicate value) { predicate = std::move(value); }
	void set(std::filesystem::path value) { path = std::move(value); }
};