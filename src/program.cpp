#include <cstdlib>

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
    
    char f = (flag.length() > 1) ? flag[1] : '\0';
    if (f == '\0')
      exit(-3);

    switch(f){
        case 'o': std::cout << "assemble!"      << std::endl; break;
        case 'm': std::cout << "expand macros!" << std::endl; break;
        case 'p': std::cout << "preprocess!"    << std::endl; break;
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


    source incode = from_file(input);
    source processed;
    preprocess(incode, processed, f == 'm');
    
    // 1. If, Equ Expanded
    if (f == 'p') {
        to_file(processed, output, ".pre");
        return 0;
    }

    // 2. Macros Expanded 
    if (f == 'm'){
        to_file(processed, output, ".mcr");
        return 0;
    }

    // (-o is implied)

    std::vector<std::string> modules;        // modules: Keeps track of the output files generated, so we can link them easily.
    ast* parsed = parse(processed, modules);
 
    link(modules);


    // to_file(linked, output, ".o");
    return 0;
}




bool to_file(source data, std::string filename, std::string extension){
    // Write to File
    std::ofstream output;
    output.open ((filename + extension).c_str());

    if (!output) return false;

    for (uint i = 0; i < data.size(); i++)
        output << data[i];
    
    // Debug Printings
    #ifdef DEBUG_PRINTFILEDATA
        while(output)
            std::cout << "" << std::endl;
    #endif
    
    output.close();
    return true;
}


source from_file(std::string filename){
    std::string   ext(".asm");
    std::ifstream input((filename + ext).c_str());

    if (!input) exit(-5);

    std::vector<std::string> res;
    
    std::string temp;
    while(input){
        std::getline(input, temp);

        // Debug Printings
        #ifdef DEBUG_PRINTFILEDATA
            std::cout << temp << std::endl;
        #endif

        res.push_back(temp.c_str());
    }
    
    return res;
}


// MODULE error.cpp (Colocar macros (error codes) em error.hpp);
void logerror(int);
void logerror(int code){
  switch(code){
    case 0: break; // Caso ideal
  
    default:
      std::cout << "[error] unknown error code: " << code << std::endl;
  }
}

