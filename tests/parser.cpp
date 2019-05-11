#include "../src/parser.h"
#include "catch.hpp"

TEST_CASE("Parsing statements", "[parsing]")
{
    REQUIRE(parse("Hallo: .data sub t0\n"
                  ".text\n"
                  "add t0, t1, t0\n"));

    REQUIRE(parse("add t0, 100(t0), t0"));
    REQUIRE(parse("add t0, 0x100, t0"));
    REQUIRE(parse("add t0, -0x100, t0"));
}
