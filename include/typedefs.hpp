<<<<<<< HEAD
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
=======
#pragma once
#include <fstream>
#include <vector>

// #define foreach(index, arr) for(unsigned int (index) = 0; (index) < arr.size(); v=arr[i], i++)
#define foreach(x,y) for (unsigned int x = 0; x < y.size(); x++)

#define vector_of_strings std::vector<std::string>
typedef vector_of_strings source;

typedef struct Token_struct {
  std::string token_string;
  int token_line;
  int token_value;
  bool label_equ;
  bool label_macro;
  bool label;
} Token_str;

#define vector_of_tokens std::vector<Token_str>

typedef std::string       symbol;
typedef vector_of_strings source;

typedef vector_of_tokens Tokens;

>>>>>>> 6f60b2239fb16e9b33ef5d7d264c35796cf272c4
