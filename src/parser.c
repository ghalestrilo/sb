#include <iostream>

#include "../inc/prep.h"

typedef enum reserved {

} keyword;

typedef struct astnode {
    AST_Node* op1;
    AST_Node* op2:
    keyword op;
} AST_Node;

typedef struct ast { 
   AST_Node* root;
} AST;


// Symbol Table
typedef std::map<std::string, int> symbol_table;

