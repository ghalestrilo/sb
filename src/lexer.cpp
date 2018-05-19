#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

#include "../include/lexer.hpp"

Token extract_label(std::vector<Token> line){
    if (!line.empty()){
        Token first_token = line.front();
        
        if (first_token.text.back() == ':'){
            first_token.text.erase(first_token.text.size() - 1);
            return first_token;
        }

        if (line.size() > 1 && (line[1].text == ":"))
            return first_token;
    }
    return Token();
}

std::vector<Token> skip_label(std::vector<Token> line){
    bool ok = false;
    Token first_token;

    while(!ok){
        ok = true;

        if (line.empty()) return line;

        first_token = line[0];

        if (first_token == ":" || first_token.text.back() == ':'){ // DO NOT ACCEPT
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

bool readline(std::string line, std::vector<Token>* tokens, unsigned int lineindex){
    if (line.empty())   return false;
    tokens->clear();
    
    while (line[0] == ' ') line.erase(0); // Trim Spaces
    if    (line[0] == ';') return false;  // Ignore Comments

    std::string buf;            // Have a buffer std::string
    std::stringstream ss(line); // Insert the std::string into a stream

    while (ss >> buf){
        // CHECAR ERROS LEXICOS
        if (lex_error(buf)) return false;
        
        tokens->push_back(Token(buf, lineindex));
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
bool lex_error(std::string t){ // , std::string prev = "")
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
    // if (prev != "SPACE" && prev != "CONST")
        return true;
    
    return false;
}