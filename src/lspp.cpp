#include <filesystem>
#include <iostream>

#include <algorithm>

#include "fn/scan_directory.h"
#include "output/print_content.h"
#include "fn/setup_config.h"
#include "fn/load_config.h"
#include "fn/executable_path.h"

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

#if defined(_WIN32) || defined(_WIN64)
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
#endif

	try {
		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);

		auto config = lspp_config();

		std::string buffer{ argv[0], '\0'};
		buffer.reserve(256);

		std::filesystem::path& executableDir = config.executableDir;

		if (fn::executable_path(executableDir)) {

			std::filesystem::path configPath = (executableDir / lspp_config::CONFIG_FILENAME);
			fn::load_config(configPath, buffer);
		}
		
		for (int i = 1; i < argc; ++i) {
			buffer.append(argv[i]);
			buffer.push_back('\0');
		}

		fn::setup_config(buffer, config);

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