#include <iostream>
#include <map>

#include "../include/typedefs.hpp"
#include "debug.h"


/* MNT
 * maps macro name to param count.
 * if MNT[<name>] returns null, macro does not exist
 */
typedef std::map<symbol, int> MNT;

/* MDT
 * maps macro name to definition (string array)
 */
typedef std::map<symbol, source> MDT;

/* Pre-Process
 * 1. Lex-scan line
 * 2. If its defined in EQU table, substitute
 * 3. Check for directve:
 *  - Macro:
 *   - Check no other Macro directive inside definition
 *   - Push lines until Endmacro
 *   - New entry into MDT and MNT
 *  - Endmacro:
 *   - Check within Macro
 *   - Otherwise, error.
 *  - If:
 *  - Equ:
 *   - Check not keyword
 *   - New entry into EQU table
 * 
 */
bool read_source_line(std::string, vector_of_tokens*,int*);

void preprocess(source&, source*, bool,vector_of_tokens*);

/* Expand Macro
 * 1. Search MNT for macro params
 * 2. Search MDT for macro def
 * 3. Substitute params for provided tokens
 * 4. Return source segment to be inserted in place on original file
 */

source expand_macro(symbol macroname); // + args (std::vector<symbol>)
bool treating_if(vector_of_tokens*);
bool treating_macro(vector_of_tokens*);
void update_label_flags(vector_of_tokens*);
void label_tokens(vector_of_tokens*);
void if_equ_output(vector_of_tokens*,source*, bool);
void separe_copy_tokens(vector_of_tokens*);
void separe_macro_tokens(vector_of_tokens*);