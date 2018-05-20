#include <iostream>
#include "debug.h"
#include "typedefs.hpp"

#include "dictionary.hpp"

/* Token Type:

 */
// typedef std::string token;

bool readline  (std::string, vector_of_tokens*,  unsigned int = 0);
bool lex_error (std::string);

vector_of_tokens skip_label   (vector_of_tokens);
Token            extract_label(vector_of_tokens);