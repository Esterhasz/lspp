#include "run_tests.h"
#include "check.h"

#include <chrono>
#include <limits>

#include "Item.h"
#include "strategy/compare/all.h"
#include "strategy/measure/all.h"
#include "strategy/predicate/all.h"
#include "strategy/priority/all.h"
#include "argument/valued_arguments.h"

#include "fn/setup_config.h"

namespace fs = std::filesystem;
using namespace std::chrono_literals;

static void case_priority() {

	Item fileA(fs::path("a"), ItemType::regular, 1, LastWrite());
	Item fileB(fs::path("b"), ItemType::regular, 0, LastWrite());

	Item dirA(fs::path("a"), ItemType::directory, 1, LastWrite());
	Item dirB(fs::path("b"), ItemType::directory, 0, LastWrite());
	
	CHECK(priority::files(fileA, dirB) == true);
	CHECK(priority::files(dirA, fileB) == false);
	CHECK(priority::files(fileA, fileB) == std::nullopt);
	CHECK(priority::files(dirA, dirB) == std::nullopt);

	CHECK(priority::directories(dirA, fileB) == true);
	CHECK(priority::directories(fileA, dirB) == false);
	CHECK(priority::directories(fileA, fileB) == std::nullopt);
	CHECK(priority::directories(dirA, dirB) == std::nullopt);

	CHECK(priority::none(fileA, fileB) == std::nullopt);
	CHECK(priority::none(fileA, dirB) == std::nullopt);
	CHECK(priority::none(dirA, fileB) == std::nullopt);
	CHECK(priority::none(dirA, dirB) == std::nullopt);
}

static void case_predicate() {
	const auto t = fs::file_time_type{} + 10h;
	const auto timePast = t - 5h;
	const auto timeFuture = t + 5h;

	Item itemLower(fs::path("apple"), ItemType::regular, 0, LastWrite());
	Item itemUpper(fs::path("Apple"), ItemType::regular, 0, LastWrite());
	Item itemOther(fs::path("banana"), ItemType::regular, 0, LastWrite());

	Item fileSmall(fs::path("small"), ItemType::regular, 100, LastWrite());
	Item fileBig(fs::path("big"), ItemType::regular, 5000, LastWrite());
	Item fileZero(fs::path("zero"), ItemType::regular, 0, LastWrite());

	Item fileFuture(fs::path("future"), ItemType::regular, 0, timeFuture);
	Item filePast(fs::path("past"), ItemType::regular, 0, timePast);

	CHECK(predicate::by_name_cs(itemLower, itemOther) == true);

	CHECK(predicate::by_name_ci(itemLower, itemOther) == true);
	CHECK(predicate::by_name_ci(itemUpper, itemOther) == true);

	CHECK(predicate::by_size(fileBig, fileSmall) == true);
	CHECK(predicate::by_size(fileSmall, fileBig) == false);
	CHECK(predicate::by_size(fileZero, fileZero) == false);

	CHECK(predicate::by_time(fileFuture, filePast) == true);
	CHECK(predicate::by_time(filePast, fileFuture) == false);
}

static void case_compare() {
	Prioritizer noPriority = priority::none;

	Item fileSmall(fs::path("small"), ItemType::regular, 100, LastWrite());
	Item fileBig(fs::path("big"), ItemType::regular, 5000, LastWrite());

	Item fileFuture(
		fs::path("future"), ItemType::regular, 0,
		fs::file_time_type{} + 15h
	);
	Item filePast(
		fs::path("past"), ItemType::regular, 0,
		fs::file_time_type{} + 5h
	);

	CHECK(compare::normal(fileBig, fileSmall, noPriority, predicate::by_size) == true);
	CHECK(compare::normal(fileSmall, fileBig, noPriority, predicate::by_size) == false);

	CHECK(compare::reversed(fileBig, fileSmall, noPriority, predicate::by_size) == false);
	CHECK(compare::reversed(fileSmall, fileBig, noPriority, predicate::by_size) == true);

	CHECK(compare::normal(fileFuture, filePast, noPriority, predicate::by_time) == true);
	CHECK(compare::reversed(fileFuture, filePast, noPriority, predicate::by_time) == false);
}

static void case_unvalued_arguments() {
	lspp_config cfg{};
	
	fn::setup_config("-R", cfg);
	CHECK(cfg.measurer == measure::recursive);

	fn::setup_config("-r", cfg);
	CHECK(cfg.comparator == compare::reversed);

	fn::setup_config("-Rr", cfg);
	CHECK(cfg.measurer == measure::recursive);
	CHECK(cfg.comparator == compare::reversed);

	fn::setup_config("-rR", cfg);
	CHECK(cfg.measurer == measure::recursive);
	CHECK(cfg.comparator == compare::reversed);

	fn::setup_config("--reversed", cfg);
	CHECK(cfg.comparator == compare::reversed);
}

static void case_valued_arguments() {
	lspp_config cfg{};

	argument::set_columns(cfg, "line,name,date,size");
	CHECK(cfg.print.columns[0] == Column::Line);
	CHECK(cfg.print.columns[1] == Column::Name);
	CHECK(cfg.print.columns[2] == Column::Date);
	CHECK(cfg.print.columns[3] == Column::Size);


	argument::set_columns(cfg, "size,date,name,line");
	CHECK(cfg.print.columns[0] == Column::Size);
	CHECK(cfg.print.columns[1] == Column::Date);
	CHECK(cfg.print.columns[2] == Column::Name);
	CHECK(cfg.print.columns[3] == Column::Line);

	argument::set_columns(cfg, "line");
	CHECK(cfg.print.columns[0] == Column::Line);

	argument::set_columns(cfg, "name");
	CHECK(cfg.print.columns[0] == Column::Name);

	argument::set_columns(cfg, "date");
	CHECK(cfg.print.columns[0] == Column::Date);

	argument::set_columns(cfg, "size");
	CHECK(cfg.print.columns[0] == Column::Size);

	argument::set_line_limit(cfg, "0");
	CHECK(cfg.print.lineLimit == 0);
	
	argument::set_line_limit(cfg, "1");
	CHECK(cfg.print.lineLimit == 1);

	size_t limit = std::numeric_limits<size_t>::max();
	argument::set_line_limit(cfg, std::to_string(limit));
	CHECK(cfg.print.lineLimit == limit);
}

static void case_char_count() {
	CHECK(utf8::char_count("") == 0);

	CHECK(utf8::char_count(" ") == 1);
	CHECK(utf8::char_count("\n") == 1);
	CHECK(utf8::char_count("\0") == 0);

	CHECK(utf8::char_count("S") == 1);
	CHECK(utf8::char_count("~") == 1);

	CHECK(utf8::char_count("é") == 1); // precomposed character
	CHECK(utf8::char_count("é") == 1); // combining acute accent
	CHECK(utf8::char_count("ñ") == 1);

	CHECK(utf8::char_count("Ф") == 1);
	CHECK(utf8::char_count("я") == 1);

	CHECK(utf8::char_count("森") == 1);
	CHECK(utf8::char_count("界") == 1);

	CHECK(utf8::char_count("あ") == 1);
	CHECK(utf8::char_count("한") == 1);
	CHECK(utf8::char_count("א") == 1);
	CHECK(utf8::char_count("ش") == 1);

	CHECK(utf8::char_count("😀") == 1);

	CHECK(utf8::char_count("Hello, мир!") == 11);
	CHECK(utf8::char_count("森SФ") == 3);
	CHECK(utf8::char_count("é森😀") == 3);
}

static void case_substring() {
	CHECK(utf8::substring("abc", 2, 1) == "c");
	CHECK(utf8::substring(" abc", 2, 1) == "b");
	CHECK(utf8::substring("Hello, мир!", 7, 3) == "мир");
	
	// combining acute accent
	CHECK(utf8::substring("éñ", 1, 1) == "ñ");
	CHECK(utf8::substring("éx", 0, 1) == "é");
	CHECK(utf8::substring("éx", 1, 1) == "x");
	CHECK(utf8::substring("éx", 0, 2) == "éx");
	CHECK(utf8::substring("éx", 1, 2) == "x");
	// ---------------------

	// precomposed character
	CHECK(utf8::substring("éñ", 1, 1) == "ñ");
	
	CHECK(utf8::substring("森SФ", 1, 2) == "SФ");
	CHECK(utf8::substring("森SФ", 0, 2) == "森S");
	CHECK(utf8::substring("é森😀", 2, 1) == "😀");
	// ---------------------

	CHECK(utf8::char_count("👨‍👩‍👧‍👦") == 1);
	CHECK(utf8::substring("A👨‍👩‍👧‍👦B", 0, 1) == "A");
	CHECK(utf8::substring("A👨‍👩‍👧‍👦B", 1, 1) == "👨‍👩‍👧‍👦");
	CHECK(utf8::substring("A👨‍👩‍👧‍👦B", 2, 1) == "B");

	CHECK(utf8::substring("abc", 0, 0) == "");
	CHECK(utf8::substring("abc", 0, 3) == "abc");
	CHECK(utf8::substring("abc", 3, 1) == "");
	CHECK(utf8::substring("abc", 10, 1) == "");
	CHECK(utf8::substring("", 0, 1) == "");

	CHECK(utf8::char_count("é👨‍👩‍👧‍👦ñ") == 3);
	CHECK(utf8::substring("é👨‍👩‍👧‍👦ñ", 0, 2) == "é👨‍👩‍👧‍👦");
	CHECK(utf8::substring("é👨‍👩‍👧‍👦ñ", 2, 1) == "ñ");
}

void run_tests() {
	case_priority();
	case_predicate();
	case_compare();
	case_unvalued_arguments();
	case_valued_arguments();
	case_char_count();
	case_substring();
}