#pragma once 
#include <iostream>
#include <map>

enum ERRCODE {
    // Lexical
    ILLEGAL_NAME,
    UNKNOWN_SEP,

    // Syntactic
    UNRESOLVED_SYM,
    UNEXPECTED_EOF,
    LABEL_RESERVED,
    MISSING_PARAM,
    ILLEGAL_PARAM
};

namespace error {

    void warn  (ERRCODE, int = -1, std::string = "");
    void error (ERRCODE, int = -1, std::string = "");
    void print (ERRCODE, int = -1, std::string = "");

    static std::map<ERRCODE, std::string> lex = {
        { ILLEGAL_NAME,   "Illegal token: "  },
        { UNKNOWN_SEP,    "Unknown symbol: " }
    };

    static std::map<ERRCODE, std::string> syn = {
        { UNRESOLVED_SYM,   "Could not resolve symbol: "           },
        { UNEXPECTED_EOF,   "Unexpected end of file."              },
        { LABEL_RESERVED,   "Label name is reserved word: "        },
        { MISSING_PARAM,    "Expression is missing parameter(s): " },
        { ILLEGAL_PARAM,    "Illegal parameter for expression: "   }
    };
}