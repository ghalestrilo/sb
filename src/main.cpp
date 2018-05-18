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