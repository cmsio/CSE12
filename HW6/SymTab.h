#ifndef SYMTAB_H
#define SYMTAB_H

/* DO NOT ADD CODE: This file is used in evaluation
 * adding comments is ok.
 */

#include <iostream>
#include "Base.h"
#include "Hash.h"
using namespace std;

class SymTab : private HashTable {
public:
	using HashTable :: Insert;
	using HashTable :: Lookup;
	using HashTable :: Write;
	SymTab (long sz) : HashTable (sz) {}
};

#endif

