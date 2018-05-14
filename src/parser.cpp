#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include <cstdlib>

#ifdef DEBUG_PARSER_SYMBOL_TABLE
    typedef symbol_table::iterator map_it;
    void print_symbol_table(symbol_table st){
        if (st.empty()) return;

        std::cout << "[parser]: Loaded Symbol Table" << std::endl;

        for (map_it it = st.begin(); it != st.end(); it++)
            std::cout << "[parser]:  " << it->first << ": " << it->second << std::endl;
    }
#endif

// Make symbol_table
bool make_symbol_table(source code, symbol_table* st){



    // lex line
    // if is label (':')
        // push label-position pair into table
        // relative

    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        print_symbol_table(*st);
    #endif // DEBUG_PARSER_SYMBOL_TABLE
    return true;
};

ast parse(source code){
    if (code.empty()) return ast();

    unsigned int pc = 0; // position counter

    // 1st pass: Symbol Table
    symbol_table st;
    if (!make_symbol_table(code, &st)) exit(-5);
    

    // 2nd pass: Build AST
    ast parsed;
    // for(unsigned int i = 0; i < code.size(); i++){
    foreach(i,code){
        parsed << parseline(code[i], &st, &pc);

        #ifdef DEBUG_PARSER_READ_LINE
            std::cout << "[parser] line (" << i << ", " << code.size() << "): " << code[i] << "\t\t-> ";
            std::cout << std::endl;
        #endif // DEBUG_PARSER_READ_LINE
    }

    return parsed;
};

// Returns a statement to be pushed ino the statement sequence (AST)
ast_node parseline(std::string line, symbol_table* st, unsigned int* pc){
    std::vector<token> tokens;
    if (!readline(line, &tokens)) exit(-6);

    
    // Parse Main Expression
    ast_node res(parseexp(tokens[0], st));

    // Parse Expression Parameters
    foreach(i, tokens){
        if(i==0) continue;
        res.params.push_back(parseexp(tokens[i], st));
    }

    (*pc) += tokens.size();
    return ast_node(expression("TESST"));
}

expression parseexp(std::string text, symbol_table* st) {
    using namespace dictionary;
    expression e(text);

    // Literal
    if (st->find(text) != st->end()){
        e.value = st->find(text)->second;
        e.isliteral = true;
        return e;
    }
    
    // Command
    if (commands.find(text) != commands.end()){
        command c = commands.find(text)->second;
        e.data.command = c.name;
        return e;
    }

    // Directive @CATCH: Technically, directives should not be parsed into expressions, right?
    if (directives.find(text) != directives.end()){
        directive d = directives.find(text)->second;
        e.data.directive = d.name;
        return e;
    }

    return e;
}