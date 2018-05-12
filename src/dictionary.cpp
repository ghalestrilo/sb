#include "../include/dictionary.hpp"

namespace dictionary {
    bool reserved(std::string word){
        return (commands   . find(word) != commands   . end())
            && (directives . find(word) != directives . end());
    };

    bool illegal(char c){
        return (c < 'A' || c > 'Z') // Non-Alphabetic
            && (c < '0' || c > '9') // Non-Numeric
            && (c != ':')           // Non-Colon
            && (c != '_');          // Non-Underscore
    };

    const std::map<token, COMMAND> generate_global_commands_table(){
        std::map<token, COMMAND> m;
        m["ADD"]    = ADD;
        m["SUB"]    = SUB;
        m["MULT"]   = MULT;
        m["DIV"]    = DIV;
        m["JMP"]    = JMP;
        m["JMPN"]   = JMPN;
        m["JMPP"]   = JMPP;
        m["JMPZ"]   = JMPZ;
        m["COPY"]   = COPY;
        m["LOAD"]   = LOAD;
        m["STORE"]  = STORE;
        m["INPUT"]  = INPUT;
        m["OUTPUT"] = OUTPUT;
        return m;
    };

    const std::map<token, DIRECTIVE> generate_global_directives_table(){
        std::map<token, DIRECTIVE> m;
        m["SECTION"]    = SECTION;
        m["SPACE"]      = SPACE;
        m["CONST"]      = CONST;
        m["EQU"]        = EQU;
        m["IF"]         = IF;
        m["MACRO"]      = MACRO;
        m["ENDMACRO"]   = ENDMACRO;
        return m;
    };
}