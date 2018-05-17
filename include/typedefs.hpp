#pragma once
#include <fstream>
#include <vector>

// #define foreach(index, arr) for(unsigned int (index) = 0; (index) < arr.size(); v=arr[i], i++)
#define foreach(x,y) for (unsigned int x = 0; x < y.size(); x++)

#define vector_of_strings std::vector<std::string>

typedef struct Token_struct {
  std::string token_string;
  unsigned int token_line;
  unsigned int token_value;
} Token_str;

#define vector_of_tokens std::vector<Token_str>

typedef std::string       symbol;
typedef vector_of_strings source;
typedef vector_of_tokens Tokens;