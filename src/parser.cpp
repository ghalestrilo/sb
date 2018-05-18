#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include "../include/debug.h"
#include <cstdlib>


#ifdef DEBUG_PARSER_SYMBOL_TABLE
    void print_symbol_table(symbol_table st){
        if (st.empty()) 
            std::cout << "[parser] : No Symbol Table Loaded"
                      << std::endl;

        else {          
            std::cout << "[parser]: Loaded Symbol Table"
                      << std::endl;

            for (auto& entry : st)
                std::cout << "  "
                          << entry.first 
                          << ": " 
                          << entry.second 
                          << std::endl;
        }
    }
#endif

// Make symbol_table
bool make_symbol_table(source code, symbol_table* st = NULL ){
    if (st == NULL) st = new symbol_table;

    int pc = 0;

    std::vector<token> tokens;
    token label;

    for(auto& line : code){
        if (!readline(line, &tokens))              continue;



        if ((label = extract_label(tokens)) == "") continue;
        // for (auto& token : skip_label(tokens)) pc++;
        pc += skip_label(tokens).size();
        
        (*st)[label] = pc;

    }


    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        print_symbol_table(*st);
    #endif // DEBUG_PARSER_SYMBOL_TABLE
    return true;
};

ast parse(source code){
    if (code.empty()) return ast();

    // 1st pass: Symbol Table
    symbol_table st;
    if (!make_symbol_table(code, &st)) exit(-5);

    // 2nd pass: Build AST
    ast parsed;
    unsigned int pc = 0;

    for(auto& line : code)
        parsed << parseline(line, &st, &pc); // TODO: Check if isn't SECTION

    #ifdef DEBUG_PARSER_AST
        std::vector<ast_node> statements = parsed.statements;
        for(auto& s : statements){
            std::cout << "[parser] "
                      << s.exp.position
                      << ": "
                      << s.exp.text;

            for(auto& p : s.params)
                std::cout << ' '
                          << p.exp.text;

            std::cout << std::endl;
        }
    #endif // DEBUG_PARSER_AST

    return parsed;
};

// Returns a statement to be pushed ino the statement sequence (AST)
ast_node parseline(std::string line, symbol_table* st, unsigned int* pc){
    std::vector<token> tokens;
    if (!readline(line, &tokens)) return ast_node();
    
    bool first = true;
    ast_node res;
    expression e;

    for(auto token : skip_label(tokens)){
        e = parseexp(token, st);

        // Set position
        e.position = (*pc);
        (*pc)++;

        // Process Directives
        switch(res.exp.data.directive){
            case CONST:
            case SPACE:
            // case SECTION:

            default: break;
        }

        if (first) res.exp = e; // Parse Primary Expression
        else       res.params.push_back(e); // Parse Expression Parameters
        first = false;
    }
    return res;
}

expression parseexp(std::string text, symbol_table* st) {
    using namespace dictionary;
    expression e(text);

    // Literal
    if (st->find(text) != st->end()){
        e.value = st->find(text)->second;
        e.isliteral = true;
        return e;
    }
    
    // Command
    if (commands.find(text) != commands.end()){
        command c      = commands.find(text)->second;
        e.data.command = c.name;
        e.value        = c.opcode;
        return e;
    }

    // Directive @CATCH: Technically, directives should not be parsed into expressions, right?
    if (directives.find(text) != directives.end()){
        directive d      = directives.find(text)->second;
        e.data.directive = d.name;
        return e;
    }

    return e;
}
