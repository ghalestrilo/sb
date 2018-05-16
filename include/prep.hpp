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
void preprocess(source&, source*, bool);

/* Expand Macro
 * 1. Search MNT for macro params
 * 2. Search MDT for macro def
 * 3. Substitute params for provided tokens
 * 4. Return source segment to be inserted in place on original file
 */

source expand_macro(symbol macroname); // + args (std::vector<symbol>)