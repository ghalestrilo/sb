#include <iostream>
#include "debug.h"
#include "typedefs.hpp"

#include "dictionary.hpp"

/* Token Type:
    - Contains either a command or a Literal
 */
typedef std::string token;

bool readline  (std::string, std::vector<token>*);
bool lex_error (std::string);