#pragma once
#include <fstream>
#include <vector>

// #define foreach(index, arr) for(unsigned int (index) = 0; (index) < arr.size(); v=arr[i], i++)
#define foreach(x,y) for (unsigned int x = 0; x < y.size(); x++)

#define vector_of_strings std::vector<std::string>
typedef vector_of_strings source;
typedef std::string       symbol;


// Token a = {"1", 2, 3};
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
#define vector_of_tokens std::vector<Token>
typedef vector_of_tokens Tokens;
