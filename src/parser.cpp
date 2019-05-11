#include "parser.h"
#include "asm.h"
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/x3.hpp>
#include <iostream>
#include <variant>

namespace x3 = boost::spirit::x3;

struct Register : public x3::symbols<IntReg> {
    Register()
    {
        for (auto reg : IntReg::_values()) {
            add(reg._to_string(), reg);
        }
    }
} reg;

auto invert = [](auto &ctx) { x3::_val(ctx) = x3::_attr(ctx); };

const x3::rule<class AssemblerProgram, std::vector<ast::AsmStatement>> asmp
    = "AssemblerProgram";
const x3::rule<class Label, ast::Label>             label       = "Label";
const x3::rule<class Directive, ast::Directive>     directive   = "Directive";
const x3::rule<class Instruction, ast::Instruction> instruction = "instruction";
const x3::rule<class Imm12, int>                    imm12       = "imm12";
const x3::rule<class InsArugment, ast::InsArgument> insarg
    = "InstructionArgument";

auto asmp_def        = *(instruction | label | directive);
auto label_def       = x3::lexeme[+x3::alpha >> ':'];
auto directive_def   = x3::lexeme['.' >> +x3::alpha];
auto instruction_def = x3::repeat(3)[x3::alpha] >> (insarg % ',');
auto imm12_def
    = ((x3::lit("0x") >> x3::hex) | x3::uint_) | (('-' >> imm12)[invert]);
auto insarg_def = (imm12 >> '(' >> reg >> ')') | reg | imm12;

bool parse(std::string input)
{
    using x3::_attr;
    using x3::double_;
    using x3::phrase_parse;
    using x3::string;

    auto first = begin(input);
    auto last  = end(input);

    std::vector<ast::AsmStatement> output;

    bool r = x3::phrase_parse(first, last, asmp, x3::space, output);

    if (first != last) // fail if we did not get a full match
    {
        std::cout << (last - first) << std::endl;
        return false;
    }
    return r;
}

BOOST_SPIRIT_DEFINE(asmp, label, directive, instruction, imm12, insarg)
BOOST_SPIRIT_INSTANTIATE(decltype(asmp),
                         std::string::const_iterator,
                         x3::phrase_parse_context<x3::space_type>::type)
BOOST_FUSION_ADAPT_STRUCT(ast::Instruction, mmenmonic, args);
BOOST_FUSION_ADAPT_STRUCT(ast::Directive, value);
BOOST_FUSION_ADAPT_STRUCT(ast::Label, value);
