#include <iostream>
#include "typedefs.hpp"

// MODULE: program.hpp
int   run      (std::string, vector_of_strings, std::string);
bool  process  (std::string, bool);

bool  from_file(std::string, vector_of_strings*);
bool  to_file  (vector_of_strings, std::string, std::string);

// Useful Overloads
bool to_file(std::string, std::string, std::string);
bool to_file(std::vector<int>, std::string, std::string);