
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]){
    using namespace std;
    std::vector<std::string> args;

    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    
    if (args.size() < 3) exit(-1); // arg error


    // Reading headers
    std::vector<std::string> headers;
    
    if (headers.size() < 3) exit(-3);
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