#include "../include/assembler.hpp"
//#include <cstdlib>

std::vector<int> assemble(ast& program) {
    #ifdef DEBUG_ASSEMBLER_PRINT_OUTPUT
        int i = 0;
    #endif // DEBUG_ASSEMBLER_PRINT_OUTPUT


    std::vector<int> output;

    for(auto& cmd : program.statements) {
        output.push_back(cmd.exp.value);


        for(auto& p : cmd.params)
            output.push_back(p.exp.value);


        #ifdef DEBUG_ASSEMBLER_PRINT_OUTPUT
            std::cout << "[assembler] line "
                      << cmd.exp.position
                      << ": "
                      << cmd.exp.value;

            for(auto& p : cmd.params)
                std::cout << ' ' << p.exp.value;
            
            std::cout << std::endl;
        #endif // DEBUG_ASSEMBLER_PRINT_OUTPUT
    }

    return output;
}