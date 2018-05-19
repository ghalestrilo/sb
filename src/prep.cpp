#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"

bool read_source_line(std::string line, vector_of_tokens* Tokens, int* linha,source* output){
    if (line.empty())   return false;
    Token_str Token,Token_1,Token_2;
    std::string temp_str;
    bool Flag_copy = false;
    while (line[0] == ' ') line.erase(0,1); // Trim Spaces
    if    (line.size() == 1)return false;    
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
            Tokens->push_back(Token);
            #ifdef DEBUG_PREP_PRINT_TOKENS
                std::cout<<Tokens->at(Tokens->size() -1).token_string<<"("
                <<Tokens->at(Tokens->size() -1).token_line<<")"<<"|";
            #endif
                output->push_back(Tokens->at(Tokens->size() -1).token_string + " ");
            #ifdef DEBUG_PREP_OUTPUT
                std::cout << output->at(output->size()-1);
            #endif // DEBUG_PREP_OUTPUT
            }
            Flag_copy = false;
        }
        else{
            Token.token_string = buf;
            Token.token_line = *linha;
            Token.token_value = 0;
            Tokens->push_back(Token);
            #ifdef DEBUG_PREP_PRINT_TOKENS
                std::cout<<Tokens->at(Tokens->size() -1).token_string<<"("
                <<Tokens->at(Tokens->size() -1).token_line<<")"<<"|";
            #endif
                output->push_back(Tokens->at(Tokens->size() -1).token_string + " ");
            #ifdef DEBUG_PREP_OUTPUT
                std::cout << output->at(output->size()-1);
            #endif // DEBUG_PREP_OUTPUT
            if (Token.token_string.compare("COPY") == 0 ||Token.token_string.compare("MACRO") == 0){
                Flag_copy = true;//set flag to true to separe tokens with commas
            }
        }
    }
    #ifdef DEBUG_PREP_PRINT_TOKENS
        std::cout<<"\n";
    #endif
    output->push_back("\n");
    #ifdef DEBUG_PREP_OUTPUT
        std::cout << output->at(output->size()-1);
    #endif // DEBUG_PREP_OUTPUT
    *linha=*linha+1;
    return true;
}

bool treating_if();
bool treating_macro();

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
        read_source_line(file[i],Tokens,&linha,output);//make the vector of tokens
        #ifdef DEBUG_PREP_INPUT
            std::cout << file[i] << std::endl;
        #endif // DEBUG_PREP_OUTPUT
    } 

    treating_if();
    if(macros){
        treating_macro();
    }



}

