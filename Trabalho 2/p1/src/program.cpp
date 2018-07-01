#include <cstdlib>
#include "../include/debug.h"

#include "../include/program.hpp"
#include "../include/prep.hpp"
#include "../include/parser.hpp"
#include "../include/assembler.hpp"
// #include "../include/linker.hpp"

// MODULE: program.cpp

/* Runs program with parsed argument
  returns 0 when ok
  otherwise returns errorcode (for logerror)
  */
int run(std::string flag, vector_of_strings files, std::string output){
    // Read Flags
    if (flag.length() < 2) exit(-3);
    if (files.size()  < 1) exit(-4);

    bool modular = (files.size() > 1);
    char mode    = flag[1];

    #define DEBUG_PROGRAM_INPUT_FILENAMES
    #ifdef DEBUG_PROGRAM_INPUT_FILENAMES
        std::cout << "[program] input files:" << std::endl;
        for (auto f : files)
            std::cout << "\t- "
                      << f
                      << std::endl;
    #endif // DEBUG_PROGRAM_INPUT_FILENAMES
    
    // Gigantic loop
    for (auto file : files){


// -------------------------------------------------------------------- Preprocess Files
        vector_of_strings prepped;
        vector_of_strings temp;
        vector_of_tokens* tokenized = new vector_of_tokens; 

        
        if (from_file(file, &temp)){
            prepped.clear();
            preprocess(temp, &prepped, mode!='p', tokenized);
        
        }

        else{
            std::cout << "Problem reading file: "
                      << file
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
        // if (to_file(assemble(*parsed), output, ".o")) exit(-10);
        if (to_file(assemble(*parsed), output, ".o")) {};

        // Cleanup
        prepped.clear();
        temp.clear();
        delete tokenized;
        delete parsed;
    }
 
    return 0;
}













// --------------------------------------------------------------------------- FILE MODULE

// Single-string overload
bool to_file(std::string data, std::string filename, std::string extension){
    std::ofstream output;
    output.open ((filename + extension).c_str());
    if (!output) return false;

    output << data;

    output.close();
    // Debug Printings
    #ifdef DEBUG_FILE_PRINTDATA
        std::cout << "[file]: " << filename << extension << std::endl;
        vector_of_strings readback;
        if (from_file(filename, &readback))
            for (std::string line : readback)
                std::cout << line << std::endl;
        else std::cout << "[file] Error opening readback file: filename" << std::endl;
    #endif
    return true;
}

bool to_file(std::vector<int> data, std::string filename, std::string extension){
    vector_of_strings bin;
    for (auto number : data) bin.push_back(std::to_string(number) + " ");

    return to_file(bin, filename, extension);
}


// Source code overload
bool to_file(vector_of_strings data, std::string filename, std::string extension){
    // Write to File
    std::ofstream output;
    output.open ((filename + extension).c_str());

    if (!output) return false;

    for (auto& line : data) output << line;

    output.close();

    // Debug Printings
    #ifdef DEBUG_FILE_PRINTDATA
        std::cout << "[file]: " << filename << extension << std::endl;

        vector_of_strings readback;
        if (from_file(filename, &readback));
            for (std::string line : readback)
                std::cout << line << std::endl;
    #endif

    return true;
}


bool from_file(std::string filename, vector_of_strings* res){
    std::string   ext(".asm");
    std::ifstream input((filename + ext).c_str());

    if (!input) return false;

    // std::vector<std::string> res = std::vector<std::string>();
    
    std::string temp;
    // while(input >> temp){
    while(std::getline(input, temp)){
        // Debug Printings
        #ifdef DEBUG_FILE_PRINTDATA
            std::cout << temp << std::endl;
        #endif

        // res.push_back(temp);
        res->push_back(std::string(temp.c_str()));
    }

    return true;
}

bool process(std::string filename, bool singlefile){
    
    return true;
}
