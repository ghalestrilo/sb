
#include <iostream>
#include <vector>
#include <unordered_map>
#include "string.h"
#include <cstdlib>
#include <string>
// #include <sstream>
#include <fstream>

// ------------------------------------------------ MACROS
#define vector_of_strings std::vector<std::string>


// ------------------------------------------------ DECLARATIONS
bool readfile  (std::string, vector_of_strings*);
bool writefile (std::string, vector_of_strings);
bool link(vector_of_strings, vector_of_strings, vector_of_strings*);

struct instruction {
    int  word;
    bool relative;
};

// ------------------------------------------------ MAIN
int main(int argc, char const *argv[]){
    using namespace std;

    // Reading Args
    vector_of_strings args;
    
    // Declaring i/o files
    vector_of_strings data1;
    vector_of_strings data2;
    vector_of_strings output;


    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    switch(args.size() - 1){
        case 0:
            std::cout << "No input files. Aborting execution." << std::endl;            
            break;

        // Cascades into case 1
        case 2:
            if (!readfile(args[2], &data2)){
                std::cout << "Error reading file: " << args[2] << std::endl;
                exit(-2);
            }
        case 1:
        
            if (!readfile(args[1], &data1)){
                std::cout << "Error reading file: " << args[2] << std::endl;
                exit(-2);
            }
            break;


        default:
            std::cout << "Too many arguments for linker: ";
            for(auto a : args)
                std::cout << a << ' ';
            std::cout << std::endl << "Aborting execution" << std::endl;
            exit(-1); 
    }

    // for(auto d : data1) std::cout << d << ' '; std::cout << std::endl;
    // for(auto d : data2) std::cout << d << ' '; std::cout << std::endl;

    if (!link(data1, data2, &output)) exit(-3);


    writefile("linked.o", output);

    // vector_of_strings output;
    return 0;
}

/** Example Code
 * H: PROG1
 * H: 12
 * H: 010010101010
 * T: 12 14 15 02 5 15 12 1 6 9 4 2
 * 
 * @ghalestrilo:
 * T: a  r  a  a  r a  r  a r a r a
 * T: 12 14 15 02 5 15 12 1 6 9 4 2
 * Suponha que não há 
*/

// FIXME: This does not work with single modules yet
bool link(vector_of_strings mod1, vector_of_strings mod2, vector_of_strings* out){
    if (mod1.empty()) return false;
    std::cout << "size: " << mod1.size() << std::endl;

    // Useful
    bool singlemod = mod2.size() < 3 || mod2[3].empty();
    
    // Destructuring Module 1
    std::string name1 = mod1[0];
    std::string size1 = mod1[1];
    std::string mask1 = mod1[2];
    std::vector<instruction> text1;

    // Split Text
    const char* temp = (char*) (mod1[3].c_str());
    int i = 0;
    do {
        const char *begin = temp;

        while(*temp != ' ' && *temp) temp++;

        text1.emplace_back(
            instruction({
                std::stoi(std::string(begin, temp)),
                (mask1[i] == '1')}));
                i++;
    } while (0 != *temp++);


    for(auto i : text1)
        std::cout << '\t'
                  << i.word
                  << " | "
                  << (i.relative ? "relative" : "absolute")
                  << std::endl;


    
    std::vector<instruction> text2;
    if(!mod2[2].empty()){
        if (mod2[3].empty()){
        std::cout << "warning: "
                  << mod2[0]
                  << " contains no valuable information, and has been ignored by the linker."
                  << std::endl;
        }
        else{
            std::string name2 = mod2[0];
            std::string size2 = mod2[1];
            std::string mask2 = mod2[2];
            temp = (char*) (mod1[3].c_str());

            i = 0;
            do{ const char *begin = temp;

                while(*temp != ' ' && *temp) temp++;

                text2.emplace_back(
                    instruction({
                        std::stoi(std::string(begin, temp)),
                        (mask2[i] == '1')}));
                        i++;
            } while (0 != *temp++);
            
            for(auto i : text2)
                std::cout << '\t'
                        << i.word
                        << " | "
                        << (i.relative ? "relative" : "absolute")
                        << std::endl;
        }
    }

    if (out == nullptr) exit(-4);

    for(auto i : text1)
        out->push_back(std::to_string(i.word) + " ");
    for(auto i : text2)
        out->push_back(std::to_string(i.relative ? i.word + text1.size(): i.word) + " ");

    return true;
}


bool writefile (std::string name, vector_of_strings data){
    std::ofstream output;
    output.open (name.c_str());

    if (!output) return false;

    for (auto& line : data) output << line;

    output.close();

    return true;
}


bool readfile(std::string name, vector_of_strings* data){
    data->clear();

    if (name.empty()) return false;

    // std::string   ext(".o");
    // std::ifstream input((name + ext).c_str());
    std::ifstream input(name);

    if (!input) return false;

    // std::vector<std::string> res = std::vector<std::string>();
    
    std::string temp;
    while(std::getline(input, temp)){
        // Debug Printings
        #ifdef DEBUG_FILE_PRINTDATA
            std::cout << temp << std::endl;
        #endif

        // res.push_back(temp);
        data->push_back(std::string(temp.c_str()));
    }

    
    /**
     * 
     * module_name = headers[0]
     * 
     * bitmask     = headers[3]
    */

    // Begin Text Processing
    std::vector<bool> bitmask;
    std::vector<int>  text;
    if (text.size() != bitmask.size()) exit (-2);
    return true;
}