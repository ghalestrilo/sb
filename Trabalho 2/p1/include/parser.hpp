#pragma once
#include <iostream>
#include <map>

#include "typedefs.hpp"
#include "dictionary.hpp"


#include "error.hpp"

struct expression {
    expression(Token t = Token()) : token(t){}

    Token token;
    int value = 0;
    int position;
    
    int param_count;
    bool relative = false;
    

    // May not be necessary
    struct {
        COMMANDCODE   command;
        DIRECTIVECODE directive;
    } data;

    // Error Logging
    void flag(ERRCODE c){ this->token.flag(c); }

    bool    haserror() { return this->token.haserror; }
    ERRCODE errcode()  { return this->token.errcode;  }
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

struct symbol {
    symbol(std::string text, int value, bool ext = false) :
        text(text),
        value(value),
        ext(ext)
        {};

    bool operator==(symbol &rhs){ return this->text == rhs.text; };

    std::string text;
    int         value;
    bool        ext; // external
};


// Typedefs
typedef std::vector <symbol>                      symbol_table;
typedef std::map    <std::string, int>            def_table;
typedef std::vector <std::pair<std::string, int>> usage_table;


// Helpers
bool declared(std::string, symbol_table);
int  retrieve(std::string, symbol_table);

bool declared(std::string, def_table);
int  retrieve(std::string, def_table);

// Core Function
bool parse (std::vector<vector_of_tokens*>, std::vector<ast>*);

/** 1st pass
 * input:
 *  1. Code, as tokens
 *  2. Local Symbol Table pointer
 * 
 * returns:
 *  Definition Table (exported variables)
 */
def_table* first_pass(vector_of_tokens*, symbol_table*);

/** 2st pass
 * input:
 *  1. Reference to output ast
 *  2. Code, as tokens, to be parsed into the ast
 *  3. Local Symbol Table
 *  4. Global Definition Table, to check for cross-references
 * 
 * returns:
 *  Usage Table (imported and local symbols)
 */
usage_table* second_pass(ast*, vector_of_tokens&, def_table&, def_table&);

// Using Usage Tables
// typedef std::map<std::string, int>              def_table;
// typedef std::vector<std::pair<std::string, int>> usage_table;

// bool parse (std::vector<vector_of_tokens>, std::vector<ast>*);

// // 1st pass
// bool first_pass(vector_of_tokens*,
//     def_table*,        usage_table*,         // Local, for use in 2nd pass
//     def_table* = NULL, usage_table* = NULL); // Global, optional

// // 2nd pass
// bool second_pass(ast*, vector_of_tokens&,
//     def_table*,        usage_table*,         // Local, mandatory
//     def_table* = NULL, usage_table* = NULL); // Global, optional
    






bool astcheck   (ast&, vector_of_strings&);

// ast_node   parseline (std::string, def_table*, unsigned int*);
expression parseexp  (Token, def_table& st);
