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

    bool singlefile = (files.size() == 1);
    char mode       = flag[1];

    vector_of_tokens tokens;
    tokens.clear();

    // FIXME module_names should be calculated by the preprocessor
    vector_of_strings module_names = files;
    // vector_of_strings module_names;
    // std::copy(files.begin(), files.end(), &module_names);




// -------------------------------------------------------------------- Preprocess Files
    std::vector<vector_of_strings> prepped_modules;
    std::vector<vector_of_tokens>  tokenized_modules; 

    vector_of_strings temp;
    vector_of_strings processed;

    vector_of_tokens  temptokens;
    for (auto f : files){
        if (from_file(f, &temp)){
            processed.clear();
            preprocess(temp, &processed, mode!='p', &temptokens);
        
        }
        else{
            std::cout << "Problem reading file: "
                      << f
                      << ". Aborting Execution"
                      << std::endl;
            exit(-5);
        }
        
        prepped_modules.push_back(processed);
        tokenized_modules.push_back(temptokens);
    }


    // Flag-controlled Outputs
    // 1. If, Equ Expanded
    if (mode == 'p') {
        for (auto p : prepped_modules) to_file(p, output, ".pre");
        return 0;
    }

    // 2. Macros Expanded 
    if (mode == 'm') {
        for (auto p : prepped_modules) to_file(p, output, ".mcr");
        return 0;
    }
    



// -------------------------------------------------------------------- Build GST, GUT
    // Problema do Parser, nao meu

// -------------------------------------------------------------------- Parse Modules
    std::vector<ast>    parsed_modules;
    std::vector<Header> headers;
    bool parse_err =    false;

    /** FIXME: 
     * parser must receive vectors now
     * parser must mark relative tokens for the assembler
     * parser must build GST, GUT (that's why it needs the vectors)
    */

    if (!parse(tokenized_modules, &parsed_modules)) exit(-6);

    for(unsigned int i = 0; i < prepped_modules.size(); i++){
        parse_err &= astcheck(parsed_modules[i], prepped_modules[i]);
    }

    if (parse_err) exit(-5);    


// -------------------------------------------------------------------- Assemble Modules
    vector_of_strings assembled_modules;
    bool write_err = false;

    // FIXME: Assembler must receive module labels, and construct headers
    for(unsigned int i = 0; i < parsed_modules.size(); i++){
        assembled_modules.push_back(assemble(parsed_modules[i], module_names[i]));

        write_err &= to_file(assembled_modules.back(), output, ".o");
    }

    if (write_err) exit(-10);
 
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
