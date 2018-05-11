#include <iostream>
#include <map>

#include "typedefs.hpp"

enum keyword {
  
};

struct terminal {
};

struct ast_node {
    struct ast_node* op1;
    struct ast_node* op2;

    bool literal;
    union {
        keyword kw;
        terminal lit;
    };
};

struct ast { 
   ast_node* root;
};


// Symbol Table
typedef std::map<std::string, int> stable;

ast* parse(source, vector_of_strings&);