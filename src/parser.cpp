#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include <cstdlib>

#ifdef DEBUG_PARSER_SYMBOL_TABLE
    typedef stable::iterator map_it;
    void print_symbol_table(stable t){
        if (t.empty()) return;

        std::cout << "[parser]: Loaded Symbol Table" << std::endl;

        for (map_it it = t.begin(); it != t.end(); it++)
            std::cout << "[parser]:  " << it->first << ": " << it->second << std::endl;
    }
#endif

ast parse(source code, vector_of_strings& modules){
    if (code.empty()) return ast();

    // 1st pass: Symbol Table
    stable symbol_table;
    if (!make_symbol_table(code, &symbol_table)) exit(-5);
    

    // 2nd pass: Build AST
    ast parsed;
    // for(unsigned int i = 0; i < code.size(); i++){
    foreach(i,code){
        parsed << parseline(code[i]);

        #ifdef DEBUG_PARSER_READ_LINE
            std::cout << "[parser] line (" << i << ", " << code.size() << "): " << code[i] << "\t\t-> ";
            std::cout << std::endl;
        #endif // DEBUG_PARSER_READ_LINE
    }

    return parsed;
};

// Make STable
bool make_symbol_table(source code, stable* table){



    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        print_symbol_table(*table);
    #endif // DEBUG_PARSER_SYMBOL_TABLE
    return true;
};

// Returns a statement to be pushed ino the statement sequence (AST)
ast_node parseline(std::string line){
    std::vector<token> tokens;
    if (!readline(line, &tokens)) exit(-6);

    return ast_node(expression("TESST"));
}
