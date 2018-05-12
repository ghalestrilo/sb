#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"

enum keyword {
  
};

struct terminal {

};

struct token_t {
    union {
        COMMAND command;
        int value; // if literal
    };

    bool literal;
    bool relative;
    int  position;
};

struct expression {
    COMMAND command;
    std::vector<token> params; // @FIX
};

// struct ast_node {
//     struct ast_node* op1;
//     struct ast_node* op2;

//     bool literal;
//     union {
//         keyword kw;
//         terminal lit;
//     };
// };

struct ast { 
//    ast_node* root;
};


// Symbol Table
typedef std::map<std::string, int> stable;

ast* parse(source, vector_of_strings&);