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
            && (c != ';')           // Non-Comment
            && (c != '_');          // Non-Underscore
    };

    const std::map<symbol, command> generate_global_commands_table(){
        std::map<symbol, command> m;
        m.insert(std::pair<symbol, command>("ADD",   command(ADD,    1, 1,  2)));
        m.insert(std::pair<symbol, command>("SUB",   command(SUB,    1, 2,  2)));
        m.insert(std::pair<symbol, command>("MULT",  command(MULT,   1, 3,  2)));
        m.insert(std::pair<symbol, command>("DIV",   command(DIV,    1, 4,  2)));
        m.insert(std::pair<symbol, command>("JMP",   command(JMP,    1, 5,  2)));
        m.insert(std::pair<symbol, command>("JMPN",  command(JMPN,   1, 6,  2)));
        m.insert(std::pair<symbol, command>("JMPP",  command(JMPP,   1, 7,  2)));
        m.insert(std::pair<symbol, command>("JMPZ",  command(JMPZ,   1, 8,  2)));
        m.insert(std::pair<symbol, command>("COPY",  command(COPY,   2, 9,  3)));
        m.insert(std::pair<symbol, command>("LOAD",  command(LOAD,   1, 10, 2)));
        m.insert(std::pair<symbol, command>("STORE", command(STORE,  1, 11, 2)));
        m.insert(std::pair<symbol, command>("INPUT", command(INPUT,  1, 12, 2)));
        m.insert(std::pair<symbol, command>("OUTPUT",command(OUTPUT, 1, 13, 2)));
        m.insert(std::pair<symbol, command>("STOP",  command(STOP,   0, 14, 1)));
        return m;
    };

    const std::map<symbol, directive> generate_global_directives_table(){
        std::map<symbol, directive> m;
        m.insert(std::pair<symbol, directive>("SECTION", directive(SECTION,  1, 0)));
        m.insert(std::pair<symbol, directive>("SPACE",   directive(SPACE,    1, -1)));
        m.insert(std::pair<symbol, directive>("CONST",   directive(CONST,    1, 1)));
        m.insert(std::pair<symbol, directive>("EQU",     directive(EQU,      1, 0)));
        m.insert(std::pair<symbol, directive>("IF",      directive(IF,       1, 0)));
        m.insert(std::pair<symbol, directive>("MACRO",   directive(MACRO,    0, 0)));
        m.insert(std::pair<symbol, directive>("ENDMACRO",directive(ENDMACRO, 0, 0)));
        return m;
    };
}