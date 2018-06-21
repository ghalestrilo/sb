#include "../include/error.hpp"
#include <string>

using namespace error;

// MODULE error.cpp (Colocar macros (error codes) em error.hpp);
void error::error(ERRCODE code, int line, std::string errinfo){
    print(code, line, errinfo);
    exit((int) code);
}

void error::print(ERRCODE code, int line, std::string errinfo){
    std::string msg;
    // Lexical
    if (error::lex.find(code) != error::lex.end())
        msg = "(lexical error) " + lex[code] + errinfo;

    //Section
    if (error::sema.find(code) != error::sema.end())
        msg = "(semantic error) " + sema[code] + errinfo;  

    // Syntax
    if (error::syn.find(code) != error::syn.end())
        msg = "(syntax error) "  + syn[code] + errinfo; 

    if (line >= 0){
        std::cout << line;
        // msg = "line " + std::string(line) + ": " + msg;  
    }

    std::cout << msg << std::endl;
}
