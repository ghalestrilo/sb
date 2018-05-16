#include <iostream>
#include "../include/prep.hpp"
// #include "../include/lexer.hpp"

void preprocess(source& file, source* output, bool macros){
    if(file.empty()) return;

    //if macro == true: Load Tables

    // Iterate through lines
        // If token (IF or EQU): Expand
        // If token (MACRO or ENDMACRO)
            // If macro == true: Expand
    // source test;


    foreach(i, file){
        #ifdef DEBUG_PREP_OUTPUT
            std::cout << file[i] << std::endl;
        #endif // DEBUG_PREP_OUTPUT
        output->push_back(file[i]);
    } 
}

