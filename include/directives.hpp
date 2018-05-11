#include <iostream>

enum DIRECTIVE { 
    SECTION  // 1-0Marcar in ́ıcio de se ̧c ̃ao de c ́odigo (TEXT)ou dados (DATA).
    SPACE0   // 1-vari ́avelReservar   1   ou   mais   endere ̧cos   demem ́oria n ̃ao-inicializada para armaze-namento de uma palavra.
    CONST    // 1-1Reservar    mem ́oria    para    armazena-mento de uma constante inteira de 16bitsem base decimal ou hexadecimal.
    EQU      // 1-0Cria  um  sinˆonimo  textual  para  ums ́ımbolo
    IF       // 1-0Instrue  o  montador  a  incluir  alinhaseguintedo c ́odigo somente se o valordo operando for 1
    MACRO    // 0-0Marcar in ́ıcio de suma MACRO. Sem-pre dentro da se ̧c ̃ao TEXT e antes doc ́odigo principal
    ENDMACRO // 0-0Marcar o fim de uma MACRO.
}

