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
        COMMAND   command;
        DIRECTIVE directive;
    };

    bool isliteral;
    bool islabel;
    bool isrelative;
    int  position;
};


struct ast_node {
    ast_node(expression exp) : exp(exp){
        
    };
    expression exp;
    std::vector<ast_node> params;
};

struct ast { 
    void operator<<(ast_node s){ statements.push_back(s); }
    std::vector<ast_node> statements;
};


// Symbol Table
typedef std::map<std::string, int> stable;


// 1st pass
bool make_symbol_table(source, stable*);

// 2nd pass
ast      parse(source, vector_of_strings&);
ast_node parseline(std::string);