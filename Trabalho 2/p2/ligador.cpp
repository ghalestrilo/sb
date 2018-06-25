
#include <iostream>
#include <vector>
#include <unordered_map>

#define vector_of_strings std::vector<std::string>

bool readfile(std::string, vector_of_strings*);
bool link(vector_of_strings, vector_of_strings, vector_of_strings*);


int main(int argc, char const *argv[]){
    using namespace std;
    vector_of_strings args;

    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    
    if (args.size() < 3) exit(-1); // arg error

    std::string module1 = args[1];
    vector_of_strings data1;

    std::string module2 = args[2];
    vector_of_strings data2;

    for(auto a : args)
        std::cout << a << ' ';
    std::cout << std::endl << "heya" << std::endl;

    // if (!readfile(module1, &data1)) exit(-2);
    // if (!readfile(module2, &data2)) exit(-2);

    // Reading headers
    // if (data1.size() < 3) exit(-3);
    // if (data2.size() < 3) exit(-3);

    // vector_of_strings output;
    // link (data1, data2, &output);
    return 0;
}

/** Construir:
 * Global Symbol Table
 * Global Offset Table
 * Global Use Table?
 * 
*/

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





bool readfile(std::string name, vector_of_strings* data){
    data->clear();
    
    
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