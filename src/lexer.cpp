#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

#include "../include/lexer.hpp"
#include "../include/dictionary.hpp"

bool readline(std::string line, std::vector<token>& tokens){
    if (line.empty()) return false;

    std::string buf; // Have a buffer std::string
    std::stringstream ss(line); // Insert the std::string into a stream

    while (ss >> buf){
        // CHECAR ERROS LEXICOS
        if (lex_error(buf)) exit(-4);
        tokens.push_back(buf);
    }



    #ifdef DEBUG_LEXER_PRINT_TOKENS
        std::stringstream debug(line); // Insert the std::string into a stream
        
        std::cout << "[lexer]: ";
        
        while (debug >> buf) std::cout << buf;
        
        std::cout << std::endl;
    #endif

    return true;
}

/* Checks for lexical errors:
    1. Token is label and reserved word.
    2. Non-const token starts with number;
*/
// TODO: pass last token as param
bool lex_error(std::string t){ // , token previous)
    using namespace dictionary;

    // 3. Token contains illegal characters
    for(char c : t)
        if(illegal(c))
            return true;

    // 1. Token is label and reserved word.
    if (t[t.size() - 1] == ':')
        if (reserved(t))
            return true;

    // 2. Non-param (CONST, SPACE) token starts with number;
    if (t[0] > '0' && t[0] < '9')
    // if (lasttoken != "SPACE" && lasttoken != "CONST")
        return true;
    
    return false;
}