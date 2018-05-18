#include <iostream>
#include "debug.h"
#include "typedefs.hpp"

#include "dictionary.hpp"

/* Token Type:

 */
typedef std::string token;

bool readline  (std::string, std::vector<token>*);
bool lex_error (std::string);

std::vector<token> skip_label   (std::vector<token>);
token              extract_label(std::vector<token>);