#include <filesystem>
#include <iostream>

#include "measure/all.h"
#include "priority/all.h"
#include "predicate/all.h"
#include "compare/all.h"

#include <algorithm>

#include "fn/scan_directory.h"
#include "fn/print_content.h"
#include "fn/setup_config.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

#if defined(_WIN32) || defined(_WIN64)
	std::system("chcp 65001 > nul");
#endif

	try {
		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);

		auto config = lspp_config(
			measure::files,
			priority::directories,
			compare::normal,
			predicate::by_name_ci, 
			fs::current_path()
		);
        
		fn::setup_config(argc, argv, config);

		auto prio = config.get<Prioritizer>();
		auto pred = config.get<Predicate>();
		auto meas = config.get<Measurer>();
		auto comp = config.get<Comparator>();

		auto content = fn::scan_directory(config.get<fs::path>(), meas);
		
		std::sort(content.begin(), content.end(), [&](const auto& a, const auto& b) { return comp(a, b, prio, pred); });

		fn::print_content(content);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}

	return 0;
}