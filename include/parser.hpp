#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"

typedef vector_of_strings source;

struct expression {
    expression(std::string t) : text(t){}

    std::string text;
    int value;          // if literal

    union {
        COMMANDCODE   command;
        DIRECTIVECODE directive;
    } data;

    bool isliteral;
    bool islabel;
    bool isrelative;
    int  position;
};


struct ast_node {
    ast_node(expression exp) : exp(exp){};
    expression exp;
    std::vector<ast_node> params;
};

struct ast { 
    void operator<<(ast_node s){ statements.push_back(s); }
    ast_node operator[](int i){ return statements[i]; }; // Bug
    std::vector<ast_node> statements;
};


// Symbol Table: rename to symbol_table
typedef std::map<std::string, int> symbol_table;


// 1st pass
bool make_symbol_table(source, symbol_table*);

// 2nd pass
ast        parse     (source);
ast_node   parseline (std::string, symbol_table*, unsigned int*);
expression parseexp  (std::string, symbol_table* st);