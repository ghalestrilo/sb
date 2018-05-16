#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include "../include/debug.h"
#include <cstdlib>

void log(std::string msg){ std::cout << "[parser] " << msg << std::endl; };

#ifdef DEBUG_PARSER_SYMBOL_TABLE
    typedef symbol_table::iterator map_it;
    void print_symbol_table(symbol_table st){
        if (st.empty()){
            std::cout << "[parser] : No Symbol Table Loaded" << std::endl;
            return;
        }

        std::cout << "[parser]: Loaded Symbol Table" << std::endl;

        for (map_it it = st.begin(); it != st.end(); it++)
            std::cout << "[parser]:  "
                      << it->first 
                      << ": " 
                      << it->second 
                      << std::endl;
    }
#endif

// Make symbol_table
bool make_symbol_table(source code, symbol_table* st){
    if (st == NULL) st = new symbol_table;

    uint pc = 0;

    std::vector<token> tokens;
    token label;

    foreach(i, code){
        // lex line
        if (!readline(code[i], &tokens)) break;
        label = tokens[0];
        
        // if (label.end()->value == ':'){

        
        // if is label (':')
        if (label[label.size()-1] == ':'){
            // push label-position pair into table
            label.erase(label.size()-1);
            (*st)[label] = pc;
            // relative

        }

        // we could search global command table for the command's length 
        foreach(t, tokens){
            pc++;
        }
    }


    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        print_symbol_table(*st);
    #endif // DEBUG_PARSER_SYMBOL_TABLE
    return true;
};

ast parse(source code){
    if (code.empty()) return ast();

    unsigned int pc = 0; // position counter

    // 1st pass: Symbol Table
    symbol_table st;
    if (!make_symbol_table(code, &st)) exit(-5);
    

    // 2nd pass: Build AST
    ast parsed;

    foreach(i,code){
        if(i+1 > code.size()) break;
        parsed << parseline(code[i], &st, &pc);
    }


    #ifdef DEBUG_PARSER_AST
        std::vector<ast_node> statements = parsed.statements;
        foreach(i, statements){
            std::cout << "[parser] "
                      << statements[i].exp.position
                      << ": "
                      << statements[i].exp.text
                      << ' ';

            foreach(j, statements[i].params) std::cout << statements[i].params[j].exp.text;
            std::cout << std::endl;
        }
    #endif // DEBUG_PARSER_AST

    return parsed;
};

// Returns a statement to be pushed ino the statement sequence (AST)
ast_node parseline(std::string line, symbol_table* st, unsigned int* pc){
    std::vector<token> tokens;
    if (!readline(line, &tokens)) ;

    
    // Parse Main Expression
    ast_node res(parseexp(tokens[0], st));
    res.exp.position = (*pc);
    
    // Parse Expresssion Parameters
    foreach(i, tokens){
        if(i==0) continue;
        (*pc)++;
        res.params.push_back(parseexp(tokens[i], st));
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
        command c = commands.find(text)->second;
        e.data.command = c.name;
        return e;
    }

    // Directive @CATCH: Technically, directives should not be parsed into expressions, right?
    if (directives.find(text) != directives.end()){
        directive d = directives.find(text)->second;
        e.data.directive = d.name;
        return e;
    }

    return e;
}