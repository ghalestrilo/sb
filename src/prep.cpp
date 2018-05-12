#include <iostream>
#include "../include/prep.hpp"

void preprocess(source& file, source& output, bool macros){

    //if macro == true: Load Tables

    // Iterate through lines
        // If token (IF or EQU): Expand
        // If token (MACRO or DEFMACRO or ENDMACRO)
            // If macro == true: Expand
    // source test;#define DEBUG_FILE_PRINTDATA
    // return test;source
}

