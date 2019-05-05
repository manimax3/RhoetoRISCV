#pragma once
#include <string>

bool parse(std::string input);
/*
 * 
 * Assembler Program: Directive | Label | Statement
 * Directive: . >> String
 * Label: String >> :
 * Statement: String >> (String % ',')
 *
 */
