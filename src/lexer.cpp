#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

#include "../include/lexer.hpp"

token extract_label(std::vector<token> line){

    if (line.empty()) return token("");
    
    token first_token = line.front();
    if (first_token.back() == ':')
        return token(first_token.substr(0, first_token.size()-1).c_str());

    if (line.size() > 1)
        if (line[1] == ":")
            return first_token;

    return token(""); // what do
}

std::vector<token> skip_label(std::vector<token> line){
    bool ok = false;
    token first_token;

    while(!ok){
        ok = true;

        first_token = line[0];

        if (first_token == ":" || first_token.back() == ':'){ // DO NOT ACCEPT
            ok = false;
            line.erase(line.begin());
        };

        if (line.size() > 1 && line[1] == ":"){
            ok = false;
            line.erase(line.begin() + 1);
        };
    }

    return line;
}

bool readline(std::string line, std::vector<token>* tokens){
    if (line.empty())   return false;
    tokens->clear();
    
    while (line[0] == ' ') line.erase(0); // Trim Spaces
    if    (line[0] == ';') return false;  // Ignore Comments

    std::string buf;            // Have a buffer std::string
    std::stringstream ss(line); // Insert the std::string into a stream

    while (ss >> buf){ 
        // CHECAR ERROS LEXICOS
        if (lex_error(buf)) return false;
        
        tokens->push_back(token(buf));
    }

    #ifdef DEBUG_LEXER_PRINT_TOKENS
        std::stringstream debug(line); // Insert the std::string into a stream
        
        std::cout << "[lexer]: ";
        
        while (debug >> buf) std::cout << buf << " ";
        
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
    // for(char c : t)
    for(unsigned int i=0; i<t.size(); i++)
        if(illegal(t[i]))
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