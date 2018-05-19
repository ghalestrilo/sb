#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"

bool read_source_line(std::string line, vector_of_tokens* Tokens, int *linha){
    if (line.empty())   return false;
    Token_str Token,Token_1,Token_2;
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
            Token.token_string = temp_str;
            Token.token_line = *linha;
            Token.token_value = 0;
            Token.label_equ = false;
            Token.label_macro = false;
            Token.label = false;
            Tokens->push_back(Token);
            }
            Flag_copy = false;
        }
        else{
            Token.token_string = buf;
            Token.token_line = *linha;
            Token.token_value = 0;
            Tokens->push_back(Token);
            if (Token.token_string.compare("COPY") == 0 ||Token.token_string.compare("MACRO") == 0){
                Flag_copy = true;//set flag to true to separe tokens with commas
            }
        }
    }
    *linha=*linha+1;
    return true;
}

bool treating_if(vector_of_tokens* Tokens){
    int linha = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (linha != it->token_line){
            std::cout << '\n';
            linha= it->token_line;
        }
        std::cout << it->token_string<<' ';
    }


    return true;
}

bool treating_macro(vector_of_tokens* Tokens){
    return true;
}

void preprocess(source& file, source* output, bool macros,vector_of_tokens* Tokens){
    if(file.empty()) return;
    int linha = 1;
    // Iterate through lines
        // If token (IF or EQU): Expand
        // If token (MACRO or ENDMACRO)
            // If macro == true: Expand
    // source test;


    //if macro == true: Load Tables
    foreach(i, file){
        read_source_line(file[i],Tokens,&linha);//make the vector of tokens
        #ifdef DEBUG_PREP_INPUT
            std::cout << file[i] << std::endl;
        #endif // DEBUG_PREP_OUTPUT
    }
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if(it->token_string.compare(0,1,":") == 0){
            Tokens->erase(it);
            (it-1)->token_string =(it-1)->token_string +':';
        }
    }// if there is a token ':', put : in the final of previous token

    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if((it+1) != Tokens->end()){
            if 
        }
    }// update label Flags

    #ifdef DEBUG_PREP_PRINT_TOKENS
    int line = Tokens->begin()->token_line;
    for (vector_of_tokens::iterator it = Tokens->begin() ; it != Tokens->end(); ++it){
        if (line != it->token_line){
            std::cout << '\n';
            line= it->token_line;
        }
        std::cout << it->token_string<<'('<<it->token_line<<')'<<' ';
    }
    std::cout << '\n';
    #endif


    treating_if(Tokens);
    if(macros){
        treating_macro(Tokens);
    }



}

