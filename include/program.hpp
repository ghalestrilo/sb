#include <iostream>
#include "typedefs.hpp"

// MODULE: program.hpp
int   run      (std::string, std::string, std::string);
bool  from_file(std::string, source*);
bool  to_file  (source, std::string, std::string);

// Useful Overloads
bool to_file(std::string, std::string, std::string);
bool to_file(std::vector<int>, std::string, std::string);