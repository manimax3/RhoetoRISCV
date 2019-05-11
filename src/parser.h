#pragma once
#include "asm.h"
#include <boost/variant.hpp>
#include <string>
#include <variant>
#include <vector>

/*
 *
 * Assembler Program: Directive | Label | Statement
 * Directive: . >> String
 * Label: String >> :
 * Statement: String >> (String % ',')
 *
 */

namespace ast {
using InsArgument = boost::variant<int, IntReg, std::tuple<int, IntReg>>;

struct Instruction {
    std::string              mmenmonic;
    std::vector<InsArgument> args;
};

struct Directive {
    std::string value;
};

struct Label {
    std::string value;
};

using AsmStatement = boost::variant<Instruction, Directive, Label>;

}

bool parse(std::string input, std::vector<ast::AsmStatement> &output);
