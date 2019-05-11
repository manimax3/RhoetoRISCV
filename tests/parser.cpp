#include "../src/parser.h"
#include "catch.hpp"

TEST_CASE("Parsing statements", "[parsing]")
{
    std::vector<ast::AsmStatement> output;

    REQUIRE(parse("Hallo: .data sub t0\n"
                  ".text\n"
                  "add t0, t1, t0\n",
                  output));

    REQUIRE(output.size() == 5);
    REQUIRE(boost::get<ast::Label>(output[0]).value == "Hallo");
    REQUIRE(boost::get<ast::Directive>(output[1]).value == "data");
    REQUIRE(boost::get<ast::Instruction>(output[2]).mmenmonic == "sub");
    REQUIRE(boost::get<ast::Instruction>(output[2]).args.size() == 1);
    REQUIRE(boost::get<ast::Instruction>(output[4]).args.size() == 3);

    REQUIRE(parse("add t0, 100(t0), t0", output));
    REQUIRE(output.size() == 1);

    REQUIRE(parse("add t0, 0x100, t0", output));
    REQUIRE(output.size() == 1);

    REQUIRE(parse("add t0, -0x100, t0", output));
    REQUIRE(output.size() == 1);
}
