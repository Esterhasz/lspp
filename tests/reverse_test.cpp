#include <catch2/catch_all.hpp>
#include "compare/reversed.h"
#include "priority/none.h"
#include "predicate/by_name_cs.h"

TEST_CASE("reverse test") {
	Item a{ "a.txt", ItemType::regular, 0 };
	Item b{ "b.txt", ItemType::regular, 0 };

	REQUIRE(compare::reversed(a, b, priority::none, predicate::by_name_cs) == false);
}
TEST_CASE("reverse test (equal names)") {
	Item a{ "b.txt", ItemType::regular, 0 };
	Item b{ "b.txt", ItemType::regular, 0 };

	REQUIRE(compare::reversed(a, b, priority::none, predicate::by_name_cs) == false);
}