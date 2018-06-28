#include <iostream>
#include <cstdlib>

// Program
#include "../include/program.hpp"

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

// MAIN
// TODO: Receive more than one input file, change how args work
int main(int argc, char *argv[]){
    if (argc < 4) exit(-1);

    // TODO
    // bool singlemodule = ...
    // Pass this variable to program chain
    
    std::string flag   = argv[1];
    std::string input  = argv[2];
    std::string output = argv[3];

    // logerror(returncode = run(flag, input, output));
    // return returncode;
    return run(flag, input, output);
}