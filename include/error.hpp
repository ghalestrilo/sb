#include <iostream>

namespace error {
    void warn  (int, std::string = "");
    void error (int, std::string = "");
}


// MODULE error.cpp (Colocar macros (error codes) em error.hpp);
void error(int code, std::string errinfo){
  switch(code){
    case 0: break; // Caso ideal
  
    default:
      std::cout << "[error] unknown error code: " << code << std::endl;
  }
}
