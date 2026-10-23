#include "run_tests.h"
#include "check.h"

#include <chrono>

#include "Item.h"
#include "strategy/compare/all.h"
#include "strategy/measure/all.h"
#include "strategy/predicate/all.h"
#include "strategy/priority/all.h"

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

void run_tests() {
	case_priority();
	case_predicate();
	case_compare();
}