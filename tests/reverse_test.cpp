#include <catch2/catch_all.hpp>
#include "strategy/compare/reversed.h"
#include "strategy/priority/none.h"
#include "strategy/predicate/by_name_cs.h"

TEST_CASE("reverse test") {
	Item a{ "a.txt", ItemType::regular, 0, LastWrite() };
	Item b{ "b.txt", ItemType::regular, 0, LastWrite() };

	REQUIRE(compare::reversed(a, b, priority::none, predicate::by_name_cs) == false);
}
TEST_CASE("reverse test (equal names)") {
	Item a{ "b.txt", ItemType::regular, 0, LastWrite() };
	Item b{ "b.txt", ItemType::regular, 0, LastWrite() };

	REQUIRE(compare::reversed(a, b, priority::none, predicate::by_name_cs) == false);
}