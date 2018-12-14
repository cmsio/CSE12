#ifndef SYMTAB_H
#define SYMTAB_H

/* DO NOT CHANGE:  This file is used in evaluation */

#include <iostream>
#include "Base.h"
#include "Tree.h"
using namespace std;

class SymTab : private Tree {
public:
	SymTab (const char * name) : Tree (name){}
	using Tree :: Insert;
	using Tree :: Lookup;
	using Tree :: Remove;
	using Tree :: Write;
};

#endif

