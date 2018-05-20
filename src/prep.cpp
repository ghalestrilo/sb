#include <iostream>
#include <sstream>
#include <algorithm>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"


// Provavelmente você quer chamar lexer::readline()
bool read_source_line(std::string        line,
                      vector_of_tokens*  tokens,
                      int*               linha,
                      vector_of_strings* output){


        if (line.empty())   return false;
    Token token,token_1tToken_2;
    std::string temp_str;
    bool Flag_copy = false;
    while (line[0] == ' ') line.erase(0,1); // Trim Spaces
    if    (line.size() == 1){
        *linha= *linha+1;
        return false;
    }    
    if    (line[0] == ';') return false;  // Ignore Comments
    std::string com = ";";
    std::string buf;            // Have a buffer std::string
    std::stringstream ss(line); // Insert the std::string into a stream

    while (ss  >> buf){
        std::transform(buf.begin(), buf.end(),buf.begin(), ::toupper);
        if (buf.compare(0,1,";")==0){
            break;
        }
        if(Flag_copy == true){//separe where are commas into differents tokens
            std::stringstream temp(buf);
            while( temp.good() ){
            std::getline( temp, temp_str, ',' );
            token.text = temp_str;
            token.line   = *linha;
            // token.token_value  = 0;     // unnecessary
            // token.label_equ    = false; // default
            // token.label_macro  = false; // default
            // token.label        = false; // default
            tokens->push_back(token);
            }
            Flag_copy = false;
        }
        else{
            token.text = buf;
            token.line = *linha;
            // Token.token_value = 0; // unnecessary
            tokens->push_back(token);
            if (token.text.compare("COPY") == 0 ||token.text.compare("MACRO") == 0){
                Flag_copy = true;//set flag to true to separe tokens with commas
            }
        }
    }
    (*linha)++;
    return true;
};

void preprocess(vector_of_strings& file,
                vector_of_strings* output,
                bool               macros,
                vector_of_tokens*  tokens){

    if(file.empty()) return;
    int linha = 1;
    // Iterate through lines
        // If token (IF or EQU): Expand
        // If token (MACRO or ENDMACRO)
            // If macro == true: Expand
    // source test;


    //if macro == true: Load Tables
    for (auto line : file){
        read_source_line(line,tokens,&linha,output);
        #ifdef DEBUG_PREP_INPUT
            std::cout << line << std::endl;
        #endif // DEBUG_PREP_INPUT
    }
    for (vector_of_tokens::iterator it = tokens->begin() ; it != tokens->end(); ++it){
        if(it->text.compare(0,1,":") == 0){
            tokens->erase(it);
            (it-1)->text =(it-1)->text +':';
        }
    }// if there is a token ':', put : in the final of previous token

    for (vector_of_tokens::iterator it = tokens->begin() ; it != tokens->end(); ++it){
        // if((it+1) != tokens->end()){
        //     if 
        // }
    }// update label Flags

    #ifdef DEBUG_PREP_PRINT_tOKENS
    int line = tokens->begin()->line;
    for (vector_of_tokens::iterator it = tokens->begin() ; it != tokens->end(); ++it){
        if (line != it->line){
            std::cout << '\n';
            line= it->line;
        }
        std::cout << it->text<<'('<<it->line<<')'<<' ';
    }
    std::cout << '\n';
    #endif


    treating_if(tokens);
    if(macros){
        treating_macro(tokens);
    }
}



bool treating_if(vector_of_tokens* tokens){
    int linha = tokens->begin()->line;
    for (vector_of_tokens::iterator it = tokens->begin() ; it != tokens->end(); ++it){
        if (linha != it->line){
            std::cout << '\n';
            linha= it->line;
        }
        std::cout << it->text<<' ';
    }


    return true;
}

bool treating_macro(vector_of_tokens* tokens){
    return true;
}
