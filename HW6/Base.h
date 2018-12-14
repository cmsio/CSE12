/* DO NOT CHANGE:  This file is needed in evaluation.  */
#ifndef BASE_H
#define BASE_H

#include <iostream>
using namespace std;

struct Base {
	virtual operator char * (void){
		return 0;
	}
	virtual operator long (void)  {		// hash function
		return 0;
	}
	virtual long operator < (Base & base) {// lessthan function
		return *this < base;
	}
	virtual long operator == (Base & base) {// isequal function
		return *this == base;
	}
	Base (void) {}				// new_element
	virtual ~Base (void) {}			// delete_element
	virtual ostream & Write (ostream &) const = 0;// write_element
};

#endif
