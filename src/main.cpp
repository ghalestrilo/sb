#include <iostream>
#include <cstdlib>

#include <vector>





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

int run(std::string, std::string, std::string);

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



/* Runs program with parsed argument
  returns 0 when ok
  otherwise returns errorcode (for logerror)
  */
int run(std::string flag, std::string input, std::string output){
    
    char f = (flag.length() > 1) ? flag[1] : '\0';
    if (f == '\0')
      exit(-3);

    switch(f){
        case 'o':
          std::cout << "assemble!"      << std::endl;
          
          break;

        case 'm':
          std::cout << "expand macros!" << std::endl;
          
          break;

        case 'p':
          std::cout << "preprocess!"    << std::endl;
          
          break;


            break;
        default:
            std::cout << "unknown operation: " << flag << std::endl;
            exit(-2);
            break;
    }

    std::cout << "[" << input << " -> " << output << "]" << std::endl;
    
    return 0;
}

// Module error.cpp (Colocar macros (error codes) em error.hpp)break;
void logerror(int);
void logerror(int code){
  switch(code){
    case 0: break; // Caso ideal
  
    default:
      std::cout << "[error] unknown error code: " << code << std::endl;
  }
}