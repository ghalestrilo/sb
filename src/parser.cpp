#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include "../include/debug.h"
#include <cstdlib>


#ifdef DEBUG_PARSER_SYMBOL_TABLE
    void print_symbol_table(symbol_table st){
        if (st.empty()) 
            std::cout << "[parser] : No Symbol Table Loaded"
                      << std::endl;

        else {          
            std::cout << "[parser]: Loaded Symbol Table"
                      << std::endl;

            for (auto& entry : st)
                std::cout << "  "
                          << entry.first 
                          << ": " 
                          << entry.second 
                          << std::endl;
        }
    }
#endif

// Make symbol_table
bool first_pass(vector_of_tokens* code, symbol_table* st = NULL ){
    if (st == NULL) st = new symbol_table;
    int pc = 0; // Parse-Relevant

    auto it = code->begin();
    while(it != code->end()){
        
        // Section Found : TODO: Make Checks
        if (it->text == "SECTION"){
            it++;

            if (it->text == "TEXT"){
                //textfound = true;
                it = code->erase(it--, it + 2); // Delete Section and following token
                continue;
            }

            if (it->text == "DATA"){
                // if (textfound == true) datafound == true;
                it = code->erase(it--, it + 2); // Delete Section and following token
                continue;
            }

            // ERROR! UNKNOWN SECTION TYPE
        }

        // Label Found -- IF we're using grab_token
        if (it->text == ":"){
            it--;
            (*st)[it->text] = pc;

            it = code->erase(it, it + 2);
            continue;
        }

        // DEPRECATE - Label found
        if (it->text.back() == ':'){
            (*st)[it->text.substr(0, it->text.size() - 1)] = pc;
            it = code->erase(it);
        }

        #ifdef DEBUG_PARSER_FIRST_PASS
            std::cout << "[first pass] : ("
                    << pc
                    << ", "
                    << it->text
                    << ")"
                    << std::endl; 

        #endif // DEBUG_PARSER_FIRST_PASS

        it++;
        pc++;
    }



    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        print_symbol_table(*st);
    #endif // DEBUG_PARSER_SYMBOL_TABLE

    // if (!(textfound && datafound)) {} // ERROR!

    return true;
};

ast parse(vector_of_tokens code_safe){
    vector_of_tokens code;

    for (auto tok : code_safe)
        code.push_back(tok);
    
    if (code.empty()) return ast();

    // 1st pass: Symbol Table, Sanitize
    symbol_table st;
    if (!first_pass(&code, &st)) exit(-5);

    // 2nd pass: Build AST
    ast parsed;
    
    // -------------------------------------- TESTING FUNCTION
    vector_of_tokens scope;
    for (auto origtoken : code){
        if (!readline(origtoken.text, &scope)) continue;

        std::cout << "[parser] testing grab_token:";
        for (auto t : scope)
            std::cout << ' ' << t.text;
        std::cout << std::endl;
    }
    // -------------------------------------------------------

    // unsigned int pc = 0;

    // for(auto& line : code)
    //     parsed << parseline(line, &st, &pc); // TODO: Check if isn't SECTION

    // #ifdef DEBUG_PARSER_AST
    //     std::vector<ast_node> statements = parsed.statements;
    //     for(auto& s : statements){
    //         std::cout << "[parser] "
    //                   << s.exp.position
    //                   << ": "
    //                   << s.exp.token.text;

    //         for(auto& p : s.params)
    //             std::cout << ' '
    //                       << p.exp.token.text;

    //         std::cout << std::endl;
    //     }
    // #endif // DEBUG_PARSER_AST

    return parsed;
};

// Returns a statement to be pushed ino the statement sequence (AST)
ast_node parseline(std::string line, symbol_table* st, unsigned int* pc){
    std::vector<Token> tokens;
    if (!readline(line, &tokens)) return ast_node();
    
    bool first = true;
    ast_node res;
    expression e;

    if ((tokens = skip_label(tokens)).empty()) return res;

    for(auto token : tokens){
        e = parseexp(token, st);
        
        // Process Directives
        switch(res.exp.data.directive){ // may crash
            case CONST:
            case SPACE:
            case SECTION:
                // if line.size();

            default: break;
        }

        // Set position
        e.position = (*pc);
        (*pc)++;


        if (first) res.exp = e;             // Parse Primary Expression
        else       res.params.push_back(e); // Parse Expression Parameters
        first = false;
    }
    return res;
}

expression parseexp(Token tok, symbol_table* st) {
    using namespace dictionary;
    expression e(tok);

    // Literal
    if (st->find(tok.text) != st->end()){
        e.value = st->find(tok.text)->second;
        // e.isliteral = true;
        return e;
    }
    
    // Command
    if (commands.find(tok.text) != commands.end()){
        command c      = commands.find(tok.text)->second;
        e.data.command = c.name;
        e.value        = c.opcode;
        return e;
    }

    // Directive @CATCH: Technically, directives should not be parsed into expressions, right?
    if (directives.find(tok.text) != directives.end()){
        directive d      = directives.find(tok.text)->second;
        e.data.directive = d.name;
        return e;
    }

    return e;
}
