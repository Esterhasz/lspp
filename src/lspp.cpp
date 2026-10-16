#include <filesystem>
#include <iostream>

#include <algorithm>

#include "fn/scan_directory.h"
#include "output/print_content.h"
#include "fn/setup_config.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

#if defined(_WIN32) || defined(_WIN64)
	std::system("chcp 65001 > nul");
#endif

	try {
		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);

		auto config = lspp_config();

		fn::setup_config(argc, argv, config);

		auto prio = config.prioritizer;
		auto pred = config.predicate;
		auto meas = config.measurer;
		auto comp = config.comparator;
		auto base = config.path;

		auto content = fn::scan_directory(base, meas);
		
		std::sort(content.begin(), content.end(), [=](const auto& a, const auto& b) { return comp(a, b, prio, pred); });

		output::print_content(content, config.print);
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
		return -1;
	}

	return 0;
}