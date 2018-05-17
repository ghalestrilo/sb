#pragma once
#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"

struct expression {
    expression(std::string t) : text(t){}

    int value = 0;
    std::string text;
    int position;

    union {
        COMMANDCODE   command;
        DIRECTIVECODE directive;
    } data;

    bool isliteral;
    bool islabel;
    bool isrelative;
};


struct ast_node {
    ast_node(expression exp) : exp(exp){};
    expression            exp;
    std::vector<ast_node> params;
};

struct ast { 
    std::vector<ast_node> statements;

    void     operator<< (ast_node s) { statements.push_back(s); };
    ast_node operator[] (int i)      { return statements[i];    }; // Bug
};


// Symbol Table: rename to symbol_table
typedef std::map<std::string, int> symbol_table;

ast parse (source);

// 1st pass
bool make_symbol_table(source, symbol_table*);

// 2nd pass
ast_node   parseline (std::string, symbol_table*, unsigned int*);
expression parseexp  (std::string, symbol_table* st);