#include <cstdlib>
#include "../include/debug.h"

#include "../include/program.hpp"
#include "../include/prep.hpp"
#include "../include/parser.hpp"
#include "../include/linker.hpp"

// MODULE: program.cpp

/* Runs program with parsed argument
  returns 0 when ok
  otherwise returns errorcode (for logerror)
  */
int run(std::string flag, std::string input, std::string output){
    
    if (flag.length() < 2) exit(-3);
    char f = flag[1];

    switch(f){
        case 'o': std::cout << "assemble! -- ";      break;
        case 'm': std::cout << "expand macros! -- "; break;
        case 'p': std::cout << "preprocess! -- ";    break;
        default:
            std::cout << "unknown operation: " << flag << std::endl;
            exit(-2);
            break;
    }

    std::cout << "[" << input << " -> " << output << "]" << std::endl;
    
    // Run Compiler

    // Read File
    std::ifstream inputfile((input + ".asm").c_str());

    if (!inputfile) exit(-4);


    source incode;
    if (!from_file(input, &incode)) exit(-5);
    // source* processed = new source;
    source processed;
    preprocess(incode, &processed, f == 'm');
    
    // 1. If, Equ Expanded
    if (f == 'p') {
        to_file(processed, output, ".pre");
        return 0;
    }

    // 2. Macros Expanded 
    if (f == 'm') {
        to_file(processed, output, ".mcr");
        return 0;
    }

    // 3. Run parser -> assembler -> linker
    // (-o is implied)

    std::vector<std::string> modules;        // modules: Keeps track of the output files generated, so we can link them easily.
    parse(processed, modules);

    //to_file(link(modules), output, ".o");
 
    return 0;
}




bool to_file(source data, std::string filename, std::string extension){
    // Write to File
    std::ofstream output;
    output.open ((filename + extension).c_str());

    if (!output) return false;

    // for (std::string line : data)
    //     output << line;

    for (unsigned int i = 0; i < data.size() ; i++)
        output << data[i];

    output.close();

    // Debug Printings
    #ifdef DEBUG_FILE_PRINTDATA
        std::cout << "[file]: " << filename << extension << std::endl;

        source readback;
        if (from_file(filename, &readback));
            for (std::string line : readback)
                std::cout << line << std::endl;
    #endif

    return true;
}


bool from_file(std::string filename, source* res){
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
