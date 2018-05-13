#include <iostream>
#include "debug.h"
#include "typedefs.hpp"

#include "dictionary.hpp"

/* Token Type:
    - Contains either a command or a Literal
 */
struct token {
    union {
        COMMAND command;
        int value; // if literal
    };

    bool isliteral;
    bool islabel;
    bool isrelative;
    int  position;
};

bool readline(std::string, std::vector<token>&);
bool lex_error(std::string);