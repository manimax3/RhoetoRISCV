#include "catch.hpp"
#include "../src/parser.h"

TEST_CASE("Parsing statements", "[parsing]")
{
	REQUIRE(parse(
				"Hallo: .data sub t0\n"
				".text\n"
				"add t0, t1, t0\n"
				));
}
