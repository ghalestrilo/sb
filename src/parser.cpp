#include "../include/parser.hpp"
#include "../include/lexer.hpp"

#define vector_of_strings std::vector<std::string>

ast parse(source code, vector_of_strings& modules){
    if (code.empty()) return ast();
    std::vector<token> tokens;
    
    std::cout << "lines read: " << code.size() << std::endl;
    for(int i = 0; i < code.size(); i++){
        std::cout << "[parser] parsing line: " << code[i] << "\t\t into: ";
        if (readline(code[i], tokens))
            for(int j = 0; j < (int) tokens.size(); j++){
                token t = tokens[j];
                std::cout << (t.isliteral ? t.value : t.command);
            }
        std::cout << std::endl;
    }

    return ast();
};

// Make STable
stable tables(source datasection){
    stable t();

};