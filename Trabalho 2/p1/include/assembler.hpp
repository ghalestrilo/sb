#include <iostream>
#include "parser.hpp"
#include "debug.h"

std::string assemble(ast, std::string);

// TRAB2
// I think we need a "getname" here
// and makeheader should go into the assembler

// Header
Header makeheader(ast);