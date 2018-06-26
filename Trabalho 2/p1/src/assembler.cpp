#include "../include/assembler.hpp"
//#include <cstdlib>

std::string assemble(ast program, std::string name) {
    std::vector<int>    instructions;
    std::string         formatted;
    Header              header;

    for(auto& cmd : program.statements) {
        instructions.push_back(cmd.exp.value);

        for(auto& p : cmd.params)
            instructions.push_back(p.exp.value);

        #ifdef DEBUG_ASSEMBLER_PRINT_OUTPUT
            std::cout << "[assembler] "
                      << cmd.exp.position
                      << "\t: "
                      << cmd.exp.value;

            for(auto& p : cmd.params)
                std::cout << ' ' << p.exp.value;
            
            std::cout << std::endl;
        #endif // DEBUG_ASSEMBLER_PRINT_OUTPUT
    }

    for(auto i : instructions){
        formatted += " ";
        formatted += i;
    }


    // FIXME: BUILD HEADER!! (from name and ast (for length and bitmask))

    #ifdef DEBUG_ASSEMBLER_PRINT_HEADERS
        std::cout << "Module: "
                  << name
                  << "\nHeader: "
                  << std::endl;
        header.print();
    #endif // DEBUG_ASSEMBLER_PRINT_HEADERS

    return formatted;
}

Header makeheader(ast prog){
    // for(auto t : prog.statements)
    //     t.exp.token.label;

    return Header({
        "test",
        123,
        "110"
    });
}