#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include "../include/debug.h"
#include <cstdlib>


//#ifdef DEBUG_PARSER_SYMBOL_TABLE
    void print_def_table(def_table st){
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
//#endif

// TODO: Change to unsigned int, returning size of code read.
def_table* first_pass(vector_of_tokens* code, symbol_table* st){
    using namespace dictionary;
    
    // Startup Checks
    // bool modular = (code->size() == 1);
    if (st == NULL) st = new symbol_table();

    // Local Tables
    def_table* definitions = new def_table();
    std::vector<std::string> add_to_definitions;
    std::vector<std::string> external;

    // FIXME !!!
    bool modular = true;

    // if (modular &&){}


    // Loop Setup
    int  pc = 0; // Parse-Relevant
    auto it = code->begin();


    /** FIXME: Error detection here is useless, because we delete the tokens
     * one possible solution is to keep an array of error-flagged tokens,
     * and check them at the end of the first pass.
     */

    // Parsing Loop
    unsigned short int rem = 0; // remove range
    while(it != code->end()){

        // Code consumption, centralized
        while (rem --> 0){
            it = code->erase(it);
            if (it == code->end())
                break;
        }
        auto next = it + 1;
        rem = 0;

        if (it == code->end()) break; // EOF
        if (it->text == "CONST") it++; /// Bypass
        if (it == code->end()) break; // EOF

        // Section Found : TODO: Make Checks
        if (it->text == "SECTION"){
            rem++;
            if (next != code->end()) { /* error */ } // EOF
            else if (next->text == "TEXT") { rem++; }
            else if (next->text == "DATA") { rem++; }
            else {
                // ERROR: UNKNOWN SECTION TYPE
            }
            continue;
        }

        // Checking for BEGIN tag in modularized files
        // if (pc == 0 && modular){
        //     if (next == code->end()) { rem++; continue; /* error */ }
        //     if (next->text != ":")   { rem++; continue; /* error */ }
        // }

        if (it->text == "BEGIN"){
            // ERROR: Either not modular, or misplaced BEGIN tag
            rem++;
            continue;
        }

        // EXTERN: Error, if not processed inside label context
        if (it->text == "EXTERN"){
            if (!modular) { /* ERROR */ }

            rem++;
            continue;
        }

        // PUBLIC: insert into global symbol table
        if (it->text == "PUBLIC"){
            if (!modular) { /* ERROR */ }

            rem++;
            if (next == code->end()) break; // EOF
            
            for(auto d : add_to_definitions)
                if (d == next->text){
                    it->flag(LABEL_MULTIEXPORT);
                    break;
                }

            add_to_definitions.push_back(next->text);
            
            rem++;
            continue;
        }

        
        // LABEL Processing
        if (next != code->end() && next->text == ":"){
            rem++;
            if (code->erase(next) != it + 1) exit(-1234);
            // next = code->erase(next);
            next = it + 1;
            std::cout << "label: "
                      << it->text
                      << " - "
                      << next->text
                      << std::endl;
            // Check for errors
            if (declared(it->text, *st))   it->flag(LABEL_REDECLARED);
            else if (reserved(it->text))   it->flag(LABEL_RESERVED);
            else {

                if(next == code->end()) /* error */
                    break;
                
                
                // EXTERN: inform usage of external symbol (to usage_table)
                if (next->text == "EXTERN"){
                    if (!modular) { /* ERROR */ }
                    st->push_back(symbol(it->text, 0, true));
                    rem++;
                }
                
                // BEGIN
                if (next->text == "BEGIN"){
                    if (!modular) { /* ERROR */ }
                    if (pc != 0)  { /* ERROR */ }
                    st->push_back(symbol(it->text, 0));
                    rem++;
                }
                
                // Regular Label
                st->push_back(symbol(it->text, pc));
            }

            continue;
        }

        #ifdef DEBUG_PARSER_FIRST_PASS
            std::cout << "[parser : 1st pass] "
                      << pc
                      << "\t: "
                      << it->text
                      << std::endl; 

        #endif // DEBUG_PARSER_FIRST_PASS

        it++;
        pc++;
    }


    #ifdef DEBUG_PARSER_SYMBOL_TABLE
        // print_def_table(*st);
    #endif // DEBUG_PARSER_SYMBOL_TABLE

    // TODO: Check if externs are ok - no undefined symbols

    for (auto entry : add_to_definitions)
        if (definitions->find(entry) != definitions->end()) // Symbol not previously defined
            if (declared(entry, *st)) // Symbol not locally undefined
                (*definitions)[entry] = retrieve(entry, *st);
            else {
                // ERR: Cannot set unknown symbol to public
            }
        else{
            // ERR: Multiple Exports of same symbol
        }
        

    return definitions;
};

usage_table* second_pass(ast* parsed, vector_of_tokens& code, def_table& st, def_table& gst){
    using namespace dictionary;
    unsigned short int args = 0;
    int pos = 0;

    if (code.empty()) return new usage_table();

    auto it = code.begin();
    while(it != code.end()){
        expression e = parseexp(*it, st);
        e.position   = pos;

        // -------------------------------------------- <Treating Directives>
        if (e.token == "CONST"){
            ++it;

            bool neg = (it->text[0] == '-');

            if (neg) ++it;

            if (it == code.end()) { // ERROR: UNEXPECTED EOF
                e.flag(UNEXPECTED_EOF);
                *parsed << ast_node(e);
                continue;
            }

            if (!numeric(it->text)){
                // ERROR!
                e.flag(ILLEGAL_PARAM);
                *parsed << ast_node(e);
                continue;
            }


            e.value = neg ? (- std::stoi(it->text)) : std::stoi(it->text);
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

        // -------------------------------------------- </Treating Directives>

        ast_node statement(e);

        if (it == code.end()) break;
        ++it;
        ++pos;

        args = e.param_count;
        while (args > 0){
            if (it == code.end()) break; // ERR unexpected EOF

            expression param = parseexp(*it, st);
            if (reserved(param.token.text))
                e.flag(ILLEGAL_PARAM);
            statement.params.push_back(param);
            
            ++it;
            ++pos;
            --args;
        };
        

        *parsed << statement;
    }

    return new usage_table();
}

expression parseexp(Token tok, def_table& st) {
    using namespace dictionary;
    expression e(tok);
    e.token.line = tok.line;

    // bool found = false;

    // Literal
    if (st.find(tok.text) != st.end()){
        e.value = st.find(tok.text)->second;
        // found = true;
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


bool astcheck   (ast& code, vector_of_strings& orig){
    unsigned short int errcount = 0;

    for (auto s : code.statements) {
        if (s.exp.haserror() == true) {
            errcount++;
            error::print(s.exp.errcode(), s.exp.token.line);
            std::cout << "\t - " 
                      << orig[s.exp.token.line] 
                      << std::endl 
                      << std::endl;
        }

        for (auto p : s.params)
            if (p.exp.haserror() == true) {
                errcount++;
                error::print(p.exp.errcode(), p.exp.token.line);
                std::cout << "\t - " 
                          << orig[p.exp.token.line] 
                          << std::endl 
                          << std::endl;
            }
    }

    // @DELETE
    std::cout << "[parser] Detected "
              << errcount 
              << " errors in "
              << code.statements.size()
              << " lines."
              << std::endl;

    return (errcount == 0);
}

// WIP
bool parse (std::vector<vector_of_tokens*> safe_sources, std::vector<ast>* outputs){
    outputs = new std::vector<ast>;

    def_table                  gdt; // Global Definition Table
    std::vector<def_table*>    dt;  // Definition Tables
    std::vector<symbol_table*> lst; // Local Symbol Tables
    


    // Copying (safety) and treating input code
    std::vector<vector_of_tokens*> sources;
    vector_of_tokens buffer;
    for (vector_of_tokens* safe_code : safe_sources){
        auto code = new vector_of_tokens;
        sources.emplace_back(code);

        for (auto origtoken : (*safe_code)){
            if (!readline(origtoken.text, &buffer, origtoken.line)) continue;
            
            
            code->insert(code->end(), buffer.begin(), buffer.end());
        }
    }


    // First-Passing Modules
    for (vector_of_tokens* s : sources){
        lst.push_back(new symbol_table);
        dt.emplace_back(first_pass(s, lst.back()));
    }

    

    #ifdef DEBUG_PARSER_GLOBAL_SYMBOL_TABLE
        std::cout << "[parser] Global Symbol Table"
                  << std::endl;
        print_def_table(gdt);
    #endif // DEBUG_PARSER_GLOBAL_SYMBOL_TABLE


    // Check for cross-dependencies, build global defs table


    // Second Pass: Coisate the bagulhettes    
    for (unsigned int i = 0; i < sources.size(); i++){
        ast parsed;
        second_pass(&parsed, *(sources[i]), *(dt[i]), gdt);
        outputs->push_back(parsed);
    }
        
    return true;
}



bool declared(std::string text, symbol_table st){
    for (auto s : st)
        if (s.text == text)
            return true;
    return false;
}

bool declared(std::string text, def_table dt){
    if (dt.find(text) != dt.end()) return true;
    return false;
}

int retrieve(std::string text, symbol_table st){
    for (auto s : st)
        if (s.text == text)
            return s.value;
    return -1;
}

int retrieve(std::string text, def_table dt){
    if (dt.find(text) != dt.end()) return dt[text];
    return -1;
}


































/*
ast parse(vector_of_tokens code_safe){
    
    vector_of_tokens code;

    // Creating local, treated copy of code
    vector_of_tokens buffer;
    for (auto origtoken : code_safe){
        if (!readline(origtoken.text, &buffer, origtoken.line)) continue;
        
        code.insert(code.end(), buffer.begin(), buffer.end());
    }

    // Can go to beginning, as code_safe
    if (code.empty()) return ast();

    // 1st pass: Symbol Table, Sanitize
    def_table st;
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
*/