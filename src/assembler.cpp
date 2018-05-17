#include "../include/assembler.hpp"
//#include <cstdlib>

std::vector<int> assemble(ast& program) {
    std::vector<int> output;

    for(auto& cmd : program.statements) {
        output.push_back(cmd.exp.value);


        for(auto& p : cmd.params)
            output.push_back(p.exp.value);


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

    return output;
}