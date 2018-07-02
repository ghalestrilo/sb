
#include <iostream>
#include <vector>
#include <unordered_map>
#include "string.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

// ------------------------------------------------ MACROS
#define vector_of_strings std::vector<std::string>


// ------------------------------------------------ DECLARATIONS
bool readfile  (std::string, vector_of_strings*);
bool writefile (std::string, vector_of_strings);
bool link(vector_of_strings, vector_of_strings, vector_of_strings*);
bool onemod(vector_of_strings, vector_of_strings*);

struct instruction {
    int  word;
    bool relative;
};

struct t_uso{
    string nome;
    int num;
}

struct t_def{
    string nome;
    int num;
}


// ------------------------------------------------ MAIN
int main(int argc, char const *argv[]){
    using namespace std;
    bool singlemod;
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
    singlemod = data2.empty();
    if (singlemod == true){
        onemod(data1,&output);
    }else if (!link(data1, data2, &output)) exit(-3);


    writefile("linked.o", output);

    // vector_of_strings output;
    return 0;
}

// FIXME: This does not work with single modules yet
bool link(vector_of_strings mod1, vector_of_strings mod2, vector_of_strings* out){
    if (mod1.empty()) return false;
    // std::cout << "size: " << mod1.size() << std::endl;
    int i = 0;
    int j = 0;
    // Destructuring Module 1
    std::string name1 = mod1[0];
    std::string size1 = mod1[1];
    std::string mask1 = mod1[2];
    std::string def1 = mod1[3];
    std::string use1 = mod1[4];
    std::string code1 = mod1[5];
    std::cout<<def1<<std::endl;
    std::cout<<use1<<std::endl;
    std::cout<<code1<<std::endl;
    std::vector<instruction> text1;
    std::vector<t_uso> tab_uso;
    std::vector<t_def> tab_def;
    std::string buf;            // Have a buffer std::string
    std::stringstream ss(code1); // Insert the std::string into a stream
    std::stringstream ssdef1(def1);
    std::stringstream ssuse1(use1);

    while (ss  >> buf){
        text1.emplace_back(
            instruction({
                std::stoi(buf),
                (mask1[i] == '1')}));
                i++;
    }


    for(auto i : text1)
        std::cout << '\t'
                  << i.word
                  << " | "
                  << (i.relative ? "relative" : "absolute")
                  << " | "
                  << i.word
                  << std::endl;

    std::vector<instruction> text2;
    std::vector<instruction> text3;
    std::string name2 = mod2[0];
    std::string size2 = mod2[1];
    std::string mask2 = mod2[2];
    std::string def2 = mod2[3];
    std::string use2 = mod2[4];
    std::string code2 = mod2[5];
    std::cout<<def2<<std::endl;
    std::cout<<use2<<std::endl;
    std::cout<<code2<<std::endl;
    std::stringstream ss2(code2); // Insert the std::string into a stream
    std::stringstream ssdef2(def2);
    std::stringstream ssuse2(use2);
    i = 0;
    while (ss2  >> buf){
        text2.emplace_back(
            instruction({
                std::stoi(buf),
                (mask2[i] == '1')}));
                i++;
    }
    for(auto i : text2)
        std::cout << '\t'
                << i.word
                << " | "
                << (i.relative ? "relative" : "absolute")
                << " | "
                << (i.relative ? i.word + text1.size(): i.word)
                << std::endl;

    text3 = text1;
    for(auto i : text2)
        text3.push_back(i);
    if (out == nullptr) exit(-4);

    for(auto i : text1)
        out->push_back(std::to_string(i.word) + " ");
    for(auto j : text2)
        out->push_back(std::to_string(j.relative ? j.word + text1.size(): j.word) + " ");
    for(auto j : text3)
        std::cout<<j.word<<"  ";

    return true;
}

bool onemod(vector_of_strings data, vector_of_strings* out){
    int i = 0;
    for(auto i : data){
        out->push_back(i);
    }
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