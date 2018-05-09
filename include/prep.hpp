#include <iostream>
#include <map>

// General Typedef

typedef std::string         token;  //
typedef std::stringstream   source; //


/* MNT
 * maps macro name to param count.
 * if MNT[<name>] returns null, macro does not exist
 */
typedef std::map<token, int> MNT;

/* MDT
 * maps macro name to definition (stringstream)
 */
typedef std::map<token, source> MDT;


/* Expand Macro
 * 1. Search MNT for macro params
 * 2. Search MDT for macro def
 * 3. Substitute params for provided tokens
 * 4. Return source segment to be inserted in place on original file
 */
source expand_macro(token macroname);


