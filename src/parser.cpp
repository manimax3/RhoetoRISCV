#include "parser.h"
#include "asm.h"
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace x3 = boost::spirit::x3;

namespace ast {
struct Statement {
    std::string         mmenmonic;
    std::vector<IntReg> regs;

    std::ostream &operator<<(std::ostream &out)
    {
        out << mmenmonic << " | ";
        for (auto reg : regs) {
            out << reg._to_string() << " ";
        }
        return out;
    }
};
}

struct Register : public x3::symbols<IntReg> {
    Register()
    {
        for (auto reg : IntReg::_values()) {
            add(reg._to_string(), reg);
        }
    }
} reg;

using AsmpValueType = boost::variant<std::string, ast::Statement>;
const x3::rule<class AssemblerProgram, std::vector<AsmpValueType>> asmp
    = "AssemblerProgram";
const x3::rule<class Label, std::string>        label     = "Label";
const x3::rule<class Directive, std::string>    directive = "Directive";
const x3::rule<class Statement, ast::Statement> statement = "Statement";

auto asmp_def      = *(statement | label | directive );
auto label_def     = x3::lexeme[+x3::alpha >> ':'];
auto directive_def = x3::lexeme['.' >> +x3::alpha];
auto statement_def = x3::repeat(3)[x3::alpha] >> (reg % ',');

struct AsmpValueVisitor : public boost::static_visitor<> {
    template<typename T>
    void operator()(T &operand) const
    {
        if constexpr (std::is_same_v<
                          std::remove_cv_t<std::remove_reference_t<T>>,
                          ast::Statement>) {
            operand << std::cout << std::endl;
        } else {
            std::cout << operand << std::endl;
        }
    }
};

bool parse(std::string input)
{
    using x3::_attr;
    using x3::double_;
    using x3::phrase_parse;
    using x3::string;

    auto first = begin(input);
    auto last  = end(input);

    std::vector<AsmpValueType> output;

    bool r = x3::phrase_parse(first, last, asmp, x3::space, output);

    if (first != last) // fail if we did not get a full match
    {
        std::cout << (last - first) << std::endl;
        return false;
    }

    for (auto &out : output) {
        boost::apply_visitor(AsmpValueVisitor{}, out);
    }
    return r;
}

BOOST_SPIRIT_DEFINE(asmp, label, directive, statement)
BOOST_SPIRIT_INSTANTIATE(decltype(asmp),
                         std::string::const_iterator,
                         x3::phrase_parse_context<x3::space_type>::type)
BOOST_FUSION_ADAPT_STRUCT(ast::Statement, mmenmonic, regs)
