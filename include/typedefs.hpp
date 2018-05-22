#pragma once
#include <fstream>
#include <vector>

#define vector_of_strings std::vector<std::string>
#define vector_of_tokens  std::vector<Token>

struct Token {
  Token(std::string text = "", int line = 0)
    : text(text), line(line) {};

    // Main structure
  std::string text;
  int line;

    // Operators for sanity
  template<typename T> void operator+= (T rhs){ text += rhs; }
  template<typename T> void operator=  (T rhs){ text = rhs;  }
  bool operator== (std::string rhs){ return text == rhs; }
  bool operator!= (std::string rhs){ return text != rhs; }
  bool empty (){ return text.empty() || text == ""; }

    // Are these necessary?
  bool label_equ   = false;
  bool label_macro = false;
  bool label       = false;

    // Useful for post-lexing error logging
  short int error = 0;
};