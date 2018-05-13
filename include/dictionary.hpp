#pragma once
#include <iostream>
#include <map>
#include "typedefs.hpp"

    enum COMMAND { 
                // Op Code Size Desc.
        ADD,    // 1    1    2  ACC <- ACC + MEM[OP]
        SUB,    // 1    2    2  ACC <- ACC - MEM[OP]
        MULT,   // 1    3    2  ACC <- ACC * MEM[OP]
        DIV,    // 1    4    2  ACC <- ACC / MEM[OP]
        JMP,    // 1    5    2  PC <- OP
        JMPN,   // 1    6    2  SeACC < 0, PC <- OP
        JMPP,   // 1    7    2  SeACC > 0, PC <- OP
        JMPZ,   // 1    8    2  SeACC = 0, PC <- OP
        COPY,   // 2    9    3  MEM[OP2] <- MEM[OP1]
        LOAD,   // 1    10   2  ACC <- MEM[OP]
        STORE,  // 1    11   2  MEM[OP] <- ACC
        INPUT,  // 1    12   2  MEM[OP] <- STDIN
        OUTPUT, // 1    13   2  STDOUT <- MEM[OP]
        STOP    // 0    14   1  STOPS   
    };

    enum DIRECTIVE { 
                 // Params  Size  Desc
        SECTION, //   1      0    Marcar in ́ıcio de se ̧c ̃ao de c ́odigo (TEXT)ou dados (DATA).
        SPACE,   //   1      v    Reservar   1   ou   mais   endere ̧cos   demem ́oria n ̃ao-inicializada para armaze-namento de uma palavra.
        CONST,   //   1      1    Reservar    mem ́oria    para    armazena-mento de uma constante inteira de 16bitsem base decimal ou hexadecimal.
        EQU,     //   1      0    Cria  um  sinˆonimo  textual  para  ums ́ımbolo
        IF,      //   1      0    Instrue  o  montador  a  incluir  alinhaseguintedo c ́odigo somente se o valordo operando for 1
        MACRO,   //   0      0    Marcar in ́ıcio de suma MACRO. Sem-pre dentro da se ̧c ̃ao TEXT e antes doc ́odigo principal
        ENDMACRO //   0      0    Marcar o fim de uma MACRO.
    };


namespace dictionary {
    // Auxiliary Methods: DO NOT USE
    const std::map<symbol, COMMAND>   generate_global_commands_table();
    const std::map<symbol, DIRECTIVE> generate_global_directives_table();

    // 
    static const std::map<symbol, COMMAND>   commands   = generate_global_commands_table();
    static const std::map<symbol, DIRECTIVE> directives = generate_global_directives_table();


    // Useful Methods
    bool reserved(std::string);
    bool illegal(char);
}


