#include <iostream>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"

void preprocess(source& file, source* output, bool macros){
    if(file.empty()) return;

    //if macro == true: Load Tables

    // Iterate through lines
        // If token (IF or EQU): Expand
        // If token (MACRO or DEFMACRO or ENDMACRO)
            // If macro == true: Expand
    // source test;

    for(int i = 0; i < file.size(); i++){
        std::cout << file[i] << std::endl;
        output->push_back(file[i]);
    
    } 
}

