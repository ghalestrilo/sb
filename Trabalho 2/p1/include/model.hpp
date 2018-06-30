#pragma once

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

    ~ast(){
        // ~statements;
    }
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

// Necessary for Parser
struct program {

    // Basic Header
    std::string       name;
    int               size;
    std::vector<bool> relative;

    // Additional Metadata
    symbol_table *st;
    def_table    *dt;
    usage_table  *ut;

    // Text
    ast *code;

    ~program(){
        delete st;
        delete dt;
        delete ut;
        delete code;
    }
};