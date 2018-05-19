#pragma once
#include <fstream>
#include <vector>

#define vector_of_strings std::vector<std::string>
#define vector_of_tokens  std::vector<Token>


// Token a = {"1", 2, 3};
struct Token {
  Token(std::string text = "", int line = 0)
    : text(text), line(line) {};

  std::string text;
  unsigned int line;

  bool operator== (std::string rhs){ return text == rhs; }


  bool error = false; // Might be useless

  // ----------------------- DELETE
  unsigned int token_value;
  // ------------------------------
};


// ------------------------------- DELETE
// typedef vector_of_strings source;
// typedef std::string       symbol;
// typedef vector_of_strings source;
// typedef vector_of_tokens Tokens;
// --------------------------------------