#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include "../include/debug.h"
#include <cstdlib>

ast parse(vector_of_tokens code_safe){
    
    vector_of_tokens code;

    // Creating local, treated copy of code
    vector_of_tokens buffer;
    for (auto origtoken : code_safe){
        if (!readline(origtoken.text, &buffer)) continue;
        
        code.insert(code.end(), buffer.begin(), buffer.end());
    }

    // Can go to beginning, as code_safe
    if (code.empty()) return ast();

    // 1st pass: Symbol Table, Sanitize
    symbol_table st;
    if (!first_pass(&code, &st)) exit(-5);

    // 2nd pass: Build AST
    ast parsed; // = second_pass(code, st)
    if (!second_pass(&parsed, code, st)) exit(-5);

    // Function
    #ifdef DEBUG_PARSER_AST
        std::vector<ast_node> statements = parsed.statements;
        for(auto& s : statements){
            std::cout << "[parser : 2nd pass] "
                      << s.exp.position
                      << "\t: "
                      << s.exp.token.text;

            for(auto& p : s.params)
                std::cout << ' '
                          << p.exp.token.text;

            std::cout << std::endl;
        }
    #endif // DEBUG_PARSER_AST

    return parsed;
};


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

bool first_pass(vector_of_tokens* code, symbol_table* st = NULL ){
    if (st == NULL) st = new symbol_table;
    int pc = 0; // Parse-Relevant

    auto it   = code->begin();
    while(it != code->end()){
        auto next = it + 1;

        if (it->text == "CONST") it++; /// Bypass

        // Section Found : TODO: Make Checks
        if (it->text == "SECTION"){
            // it++;


            if (next != code->end() && next->text == "TEXT"){
                //textfound = true;
                it = code->erase(it, it + 2); // Delete Section and following token
                continue;
            }

            if (next != code->end() && next->text == "DATA"){
                // if (textfound == true) datafound == true;
                it = code->erase(it, it + 2); // Delete Section and following token
                continue;
            }

            // ERROR! UNKNOWN SECTION TYPE
        }

        // Label Found -- IF we're using grab_token
        if (next != code->end() && next->text == ":"){

            // Check if not reserved
            (*st)[it->text] = pc;

            it = code->erase(it, it + 2);
            continue;
        }

        #ifdef DEBUG_PARSER_FIRST_PASS
            std::cout << "[parser : 1st pass] "
                      << pc
                      << "\t: "
                      << it->text
                    //   << ")"
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

bool second_pass(ast* parsed, vector_of_tokens& code, symbol_table& st){
    unsigned short int args = 0;
    int pos = 0;

    if (code.empty()) return false;

    auto it = code.begin();
    while(it != code.end()){
        expression e = parseexp(*it, st);
        e.position   = pos;

        
        if (e.token == "CONST"){
            ++it;

            if (it == code.end()) {
                // ERROR: UNEXPECTED EOF
            }

            if (!numeric(it->text)){
                // ERROR!
            }


            e.value = std::stoi(it->text);
            *parsed << ast_node(e);

            ++it;
            continue;
        }


        else if (e.token == "SPACE"){
            ++it;
            
            args = 1;
            if (it != code.end() && numeric(it->text))
                args = std::stoi(it->text);
            
            while (args --> 0){
                *parsed << ast_node(expression(e));
                ++pos;
            }

            continue;
        }

        ast_node statement(e);

        if (it == code.end()) break;
        ++it;
        ++pos;

        args = e.param_count;
        while (args > 0){
            if (it == code.end()) break; // ERR unexpected EOF

            expression param = parseexp(*it, st);
            // if (reserved(param.token.text)) {} // ERR invalid parameter
            statement.params.push_back(param);
            
            ++it;
            ++pos;
            --args;
        };
        

        *parsed << statement;
    }

    return true;
}

expression parseexp(Token tok, symbol_table& st) {
    using namespace dictionary;
    expression e(tok);

    // Literal
    if (st.find(tok.text) != st.end()){
        e.value = st.find(tok.text)->second;
        // e.isliteral = true;
        return e;
    }
    
    // Command
    if (commands.find(tok.text) != commands.end()){
        command c      = commands.find(tok.text)->second;
        e.data.command = c.name;
        e.value        = c.opcode;
        e.param_count  = c.param_count;
        return e;
    }

    // Directive @CATCH: Technically, directives should not be parsed into expressions, right?
    if (directives.find(tok.text) != directives.end()){
        directive d      = directives.find(tok.text)->second;
        e.data.directive = d.name;
        e.param_count    = d.param_count;
        return e;
    }

    return e;
}



// // Returns a statement to be pushed ino the statement sequence (AST)
// ast_node parseline(std::string line, symbol_table* st, unsigned int* pc){
//     std::vector<Token> tokens;
//     if (!readline(line, &tokens)) return ast_node();
    
//     bool first = true;
//     ast_node res;
//     expression e;

//     if ((tokens = skip_label(tokens)).empty()) return res;

//     for(auto token : tokens){
//         e = parseexp(token, st);
        
//         // Process Directives
//         switch(res.exp.data.directive){ // may crash
//             case CONST:
//             case SPACE:
//             // case SECTION:
//                 // if line.size();

//             default: break;
//         }

//         // Set position
//         e.position = (*pc);
//         (*pc)++;


//         if (first) res.exp = e;             // Parse Primary Expression
//         else       res.params.push_back(e); // Parse Expression Parameters
//         first = false;
//     }
//     return res;
// }
