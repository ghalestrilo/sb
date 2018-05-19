#include <iostream>
#include "debug.h"
#include "typedefs.hpp"

#include "dictionary.hpp"

/* Token Type:

 */
// typedef std::string token;

bool readline  (std::string, std::vector<Token>*,  unsigned int = 0);
bool lex_error (std::string);

std::vector<Token> skip_label   (std::vector<Token>);
Token              extract_label(std::vector<Token>);