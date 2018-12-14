#ifndef STACK_H
#define STACK_H

/* DO NOT ADD CODE: This file is used in evaluation
 * adding comments is ok.
 */

#include <iostream>
#include "List.h"
using namespace std;

class Stack : private List {
public:
	using List :: IsEmpty;
	using List :: NumElements;
	using List :: Write;

	Base * Pop (void);
	Base * Push (Base *);
	const Base * Top (void) const;
};

#endif
