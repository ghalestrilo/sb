#include <cstdlib>
#include "../include/debug.h"

#include "../include/program.hpp"
#include "../include/prep.hpp"
#include "../include/parser.hpp"
#include "../include/assembler.hpp"
#include "../include/file.hpp"

int run(std::string flag, vector_of_strings files, std::string output){
    // Read Flags
    if (flag.length() < 2) exit(-3);
    if (files.size()  < 1) exit(-4);

    bool modular = (files.size() > 1);
    char mode    = flag[1];

    
    #ifdef DEBUG_PROGRAM_INPUT_FILENAMES
        std::cout << "[program] input files:" << std::endl;
        for (auto f : files)
            std::cout << "\t- "
                      << f
                      << std::endl;
    #endif // DEBUG_PROGRAM_INPUT_FILENAMES
    
    // Gigantic loop
    for (auto file : files) process(file, mode, modular);
    return 0;
}




bool process(std::string filename, char mode, bool modular){
    
// -------------------------------------------------------------------- Preprocess Files
    vector_of_strings prepped;
    vector_of_strings temp;
    vector_of_tokens* tokenized = new vector_of_tokens; 

    // Ties input name to output name
    std::string output(filename);

    
    if (from_file(filename, &temp)){
        prepped.clear();
        preprocess(temp, &prepped, mode!='p', tokenized);
    
    }

    else{
        std::cout << "Problem reading file: "
                << filename
                << ". Aborting Execution"
                << std::endl;
        exit(-5);
    }

    // Flag-controlled Outputs
    // 1. If, Equ Expanded
    if (mode == 'p') {
        to_file(prepped, output, ".pre");
        return 0;
    }

    // 2. Macros Expanded 
    if (mode == 'm') {
        to_file(prepped, output, ".mcr");
        return 0;
    }


// -------------------------------------------------------------------- Parse Modules
    program* parsed = new program();

    if (!parse(tokenized, parsed, modular)) exit(-6);
    if (!astcheck(parsed->code, prepped))  exit(-5);    

// -------------------------------------------------------------------- Assemble Modules
    std::string as = assemble(*parsed, modular);
    // std::cout << as <<std::endl;
    if (!to_file(as, output, ".o")) exit(-10);

    // Cleanup
    prepped.clear();
    temp.clear();
    delete tokenized;
    delete parsed;
    
    return true;
}