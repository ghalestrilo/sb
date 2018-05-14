#pragma once
#include <iostream>
#include <map>
#include "typedefs.hpp"


    enum COMMANDCODE { 
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

    struct command {
        command(COMMANDCODE name, unsigned short int param_count, unsigned short int opcode, short int size) : name(name), param_count(param_count), opcode(opcode) {};
        
        COMMANDCODE name;
        unsigned short int param_count;
        unsigned short int opcode;
        short int size;
    };

    enum DIRECTIVECODE { 
                 // Params  Size  Desc
        SECTION, //   1      0    Marcar in ́ıcio de se ̧c ̃ao de c ́odigo (TEXT)ou dados (DATA).
        SPACE,   //   1      v    Reservar   1   ou   mais   endere ̧cos   demem ́oria n ̃ao-inicializada para armaze-namento de uma palavra.
        CONST,   //   1      1    Reservar    mem ́oria    para    armazena-mento de uma constante inteira de 16bitsem base decimal ou hexadecimal.
        EQU,     //   1      0    Cria  um  sinˆonimo  textual  para  ums ́ımbolo
        IF,      //   1      0    Instrue  o  montador  a  incluir  alinhaseguintedo c ́odigo somente se o valordo operando for 1
        MACRO,   //   0      0    Marcar in ́ıcio de suma MACRO. Sem-pre dentro da se ̧c ̃ao TEXT e antes doc ́odigo principal
        ENDMACRO //   0      0    Marcar o fim de uma MACRO.
    };


    struct directive {
        directive(DIRECTIVECODE name, unsigned short int param_count, short int size) : name(name), param_count(param_count), size(size) {};
        
        DIRECTIVECODE name;
        unsigned short int param_count;
        short int size; // @FIXME: should not be unsigned, so we can represent variable size with a negative number for SPACE
    };

namespace dictionary {
    // Auxiliary Methods: DO NOT USE
    const std::map<symbol, command>   generate_global_commands_table();
    const std::map<symbol, directive> generate_global_directives_table();
    const std::map<symbol, command>   generate_global_commands_definition_table();
    const std::map<symbol, directive> generate_global_directives_definition_table();

    // 
    static std::map<symbol, command>   commands   = generate_global_commands_table();
    static std::map<symbol, directive> directives = generate_global_directives_table();


    // Useful Methods
    bool reserved(std::string);
    bool illegal(char);
}


