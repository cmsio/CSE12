/**
 * Name: ChakMan SIo
 * Class: CSE 12
 * Account cs12xef
 * Quarter: Fall 2016
 * Assignment: HW6 
 * File name: Driver.c
 * Class Description: This class allow user to acces all 
 *                    the ucsd student, we can use those
 *                    operator in Hash.c
 *              
 */

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include "Base.h"
#include "SymTab.h"
#include <cstdlib>
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

class UCSDStudent : public Base {
	char * name;
	long studentnum;
public:
	UCSDStudent (char * nm, long sn) :
  name (strdup (nm)), studentnum (sn) {}
	~UCSDStudent (void) {
    free (name);
	}
  // get name in c++
  operator char * (void) {  
    return name;  
  }

  operator long (void) ;  
	// operator is equal
  long operator == (Base & base)  {  
    return ! strcmp (name, base);  
  } 
  // operator is less than
  long operator < (Base & base) {
		return (strcmp (name, base) < 0) ? 1 : 0;
  }

  ostream & Write (ostream & stream) const {
		return stream << "name:  " << name
			<< "  Studentnum:  " << studentnum;
	}
};

/* You may have one or more functions defined here, too */
UCSDStudent :: operator long(void) {
  // it is for calculate ascii sum
  long sum = 0;  
    for (long index = 0; name[index]; index++) 
      sum += name[index];
      return sum; 
}


int main (int argc, char * const * argv) {
	SymTab ST (5);
	char buffer[128];
	char command;
	long number;
	char option;

	/* initialize debug variable */
	HashTable::Set_Debug(0);

	 /* check command line options for debug display */
	 while ((option = getopt (argc, argv, "x")) != EOF) {

		 switch (option) {
			 case 'x': HashTable::Set_Debug(1);
				 break;
		 	}
	} 

	ST.Write (cout << "Initial Symbol Table:\n");
	while (cin) {
		command = NULL;		// reset command each time in loop
		cout << "Please enter a command:  ((i)nsert, (l)ookup, (w)rite):  ";
		cin >> command;

		switch (command) {
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			if(!ST.Insert (new UCSDStudent (buffer, number))){

				ST.Write (cout << "\nFinal Symbol Table:\n");
				exit (0);
			}
			break;

		case 'l': {
			const Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST.Lookup (& stu);
			
			if (found)
				found->Write (cout << "Student found!!!\n") << "\n";
			else
				cout << "Student " << buffer << " not there!\n";
			}
			break;

		case 'w':
			ST.Write (cout << "The Symbol Table contains:\n");
		}
	}
	ST.Write (cout << "\nFinal Symbol Table:\n");
}

