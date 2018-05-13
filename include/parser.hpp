#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"

/* Expression Type:
    For use in the AST.
    Not sure it will be useful.
 */
struct expression {
    COMMAND command;
    // std::vector<token> params; // @FIX
};

/*
struct ast_node {
    struct ast_node* op1;
    struct ast_node* op2;

    bool literal;
    union {
        keyword kw;
        terminal lit;
    };
};
*/

struct ast { 
    // std::vector<ast_node> statements;
};


// Symbol Table
typedef std::map<std::string, int> stable;

ast parse(source, vector_of_strings&);

// 1st pass
stable tables(source);