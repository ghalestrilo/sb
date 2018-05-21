#pragma once
#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"

struct expression {
    expression(Token t = Token()) : token(t){}

    Token token;
    int value = 0;
    int position;
    
    int param_count;

    // May not be necessary
    union {
        COMMANDCODE   command;
        DIRECTIVECODE directive;
    } data;
};


struct ast_node {
    ast_node(expression exp = expression()) : exp(exp){};
    expression            exp;
    std::vector<ast_node> params;
};

struct ast { 
    std::vector<ast_node> statements;

    void     operator<< (ast_node s) { statements.push_back(s); };
    ast_node operator[] (int      i) { return statements[i];    }; // Bug?
};


// Symbol Table: rename to symbol_table
typedef std::map<std::string, int> symbol_table;

ast parse (vector_of_tokens);

// 1st pass
bool first_pass(vector_of_tokens*, symbol_table*);

// 2nd pass
ast_node   parseline (std::string, symbol_table*, unsigned int*);
expression parseexp  (Token, symbol_table* st);