#include <iostream>
#include <map>

enum keyword {
  
};

struct ast_node {
    struct ast_node* op1;
    struct ast_node* op2;
    keyword op;
};

struct ast { 
   ast* root;
};


// Symbol Table
typedef std::map<std::string, int> stable;

