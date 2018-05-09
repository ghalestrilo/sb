#include <iostream>
#include <cstdlib>

// Program
#include "../include/prep.hpp"





/* Args
 * [1]: Operacao (flag)
 * [2]: Arquivo de entrada (texto, sem extensao (infere-se .asm))
 * [3]: Arquivo de saida (sem extensao)
 *
 * Flags:
 * -p (preprocessador)  => .pre (processa apenas expressoes IF e EQU)
 * -m (macros)          => .mcr (processa macros)
 * -o (montagem)        => .o   (monta o codigo fonte dado)
 *
 */

// MODULE: program.hpp
int run(std::string, std::string, std::string);
bool to_file(source, std::string, std::string);

// MAIN
int main(int argc, char *argv[]){
    // int returncode;
    
    if (argc < 4) exit(-1);

    std::string flag   = argv[1];
    std::string input  = argv[2];
    std::string output = argv[3];

    // logerror(returncode = run(flag, input, output));
    // return returncode;
    return run(flag, input, output);
}


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


    // Run Preprocessor (ifstream -> stringstream)
    source processed;
    preprocess(inputfile, processed, f == 'm');
    if (f == 'p') {
        to_file(processed, output, ".pre");
        return 0;
    }

    // Run 
    if (f == 'm'){
        to_file(processed, output, ".mcr");
        return 0;
    }

    // Run 
    // (-o is implied)
        
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

// MODULE error.cpp (Colocar macros (error codes) em error.hpp);
void logerror(int);
void logerror(int code){
  switch(code){
    case 0: break; // Caso ideal
  
    default:
      std::cout << "[error] unknown error code: " << code << std::endl;
  }
}

