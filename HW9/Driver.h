/**
 *Name: ChakMan Sio, Mengyu Yang, 
 *PIN: cs12xef, cs12xfh
 *File name: Driver.h
 *Desceiption: this file implements the UCSDStudent class 
 *Class name: UCSDStudent
 *Description: this file implements UCSDStudent objects,
 *			       contains constructror, the getter method to 
 *			       get the name of student, two operator methods 
 *			       to compare between different objects. 
 */

#ifndef DRIVER_H
#define DRIVER_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class UCSDStudent {
        friend ostream & operator << (ostream &, const UCSDStudent &);
				/*name array*/
        char name[16];
				/*to store student number*/
        long studentnum;
public:
/**
 *Name: UCSDStudent
 *Description: the UCSDStudent constructor to initialize the object
 *Input: none
 *Output: none
 */
	
  UCSDStudent(void) : studentnum(0){
		memset(name, '\0', sizeof(name));
	}
/*
 *Name: UCSDStudent constructor
 *Description: this constructor constructs UCSDStudent onjects
 *Input: char *nm:			the contents to be construted
 *       long val:			the student number to be stored
 * 
 */
	UCSDStudent(char *nm, long val =0) : studentnum(val){
    memset(name,'\0', sizeof(name));
		strcpy(name,nm);
  }

	
/**
 *Name: char *
 *Description: this method is used to get the name of UCSDStudent method
 *Input: void
 *Output: return the name of object
 */
	operator const char * (void) const{
		return name;
	}
	
/**
 *Name: ==
 *Description: this method is used to compare two objects
 *Input: UCSD & student
 *Output: the result of comparison
 */
	long operator == (const UCSDStudent & bbb) const{
		return ! strcmp(name, bbb);
	}

/**
 *Name: <
 *Description: this method is used to comapre the two objects
 *Input: UCSDStudent & student
 *Output: reurn true if current is smaller, false otherwise
 */
	long operator < (const UCSDStudent & bbb) const{
		return (strcmp (name, bbb) < 0) ? 1 : 0;
	}
};

#endif
