/**
 *Name: ChakMan Sio, Mengyu Yang
 *Class: CSE12
 *Account: cs12xef, cs12xfh
 *Assignment: HW9
 *File Name: Driver.c
 *Description: this fiel handles the input to pup up different prompts and
 *			       call corresponding methods to run the program. 
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <getopt.h>
#include "Driver.h"
#include "SymTab.h"
#include <fstream>
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif


ostream & operator << (ostream & stream, const UCSDStudent & stu) {
        return stream << "name:  " << stu.name
                << " with studentnum:  " << stu.studentnum;
}

/*
 *Name: main
 *Description: the main method to run the program, uses the switch case to 
 *			handle differnt input and then calling correspond methods
 *
 */
int main (int argc, char * const * argv) {
        char buffer[BUFSIZ];
        char command;
        long number;
        char option;
        
				/*initialize the input stream*/
		    istream * is;
		    is = &cin;
				/*initialize the output stream*/
		    ostream * os;
		    os = &cout;

        SymTab<UCSDStudent>::Set_Debug_Off ();

        while ((option = getopt (argc, argv, "x")) != EOF) {

        switch (option) {
                case 'x': SymTab<UCSDStudent>::Set_Debug_On ();
                        break;
                }
        }
        
				SymTab<UCSDStudent> ST("Driver.datafile");
        ST.Write (cout << "Initial Symbol Table:\n" );

       	while (cin) {
								
								if (!(*is)){
								    // delete the is
                    delete is;
										delete os;
										// is store the address of cin
                    is = &cin;
										// os store the address of cout
                    os = &cout;
								}
                command = NULL;         // reset command each time in loop
                *os << "Please enter a command ((f)ile, (i)nsert, "
                        << "(l)ookup, (r)emove, (w)rite):  ";
                *is >> command;

                switch (command) {
                        
                case 'i': {
                        *os << "Please enter UCSD student name to insert:  ";
                        *is >> buffer;  // formatted input

                        *os << "Please enter UCSD student number:  ";
                        *is >> number;

                        UCSDStudent stu (buffer, number);

                        // create student and place in symbol table
                        ST.Insert (stu);
                        break;
                }
								case 'l': {
                        unsigned long found;    // whether found or not

                        *os << "Please enter UCSD student name to lookup:  ";
                        *is >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        found = ST.Lookup (stu);
                        
                        if (found)
                                cout << "Student found!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                }
                case 'r': { 
                        unsigned long removed;

                        *os << "Please enter UCSD student name to remove:  ";
                        *is >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        removed = ST.Remove(stu);

                        if (removed)
                                cout << "Student removed!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                }
								/*the file case for this program*/
							  case 'f':{
												/*output prompt*/
                        *os <<"Please enter file name for commands";
                        *is >> buffer;  // formatted input
												/*transet to another file*/
												if (is !=&cin){
                            delete is;
														/*assign a new ifstream*/
												    is = new ifstream(buffer);
														break;
												}
                         
												/*new output stream to store buffer*/
												is = new ifstream(buffer);
												/*new input stream to store null*/
												os = new ofstream("dev/null");
												break;

								}

                case 'w':{
                        ST.Write (cout << "The Symbol Table contains:\n");
								}
                }
				}
		
        ST.Write (cout << "\nFinal Symbol Table:\n");
        /*calculate the efficiency of the program afterEOF*/      
					if (ST.GetOperation() != 0) {
				      /*get cost*/
				      cout << "\nCost of operations: ";
			        cout << ST.GetCost();
			        cout << " tree accesses";
              /*get opration*/
			        cout << "\nNumber of operations: ";
			        cout << ST.GetOperation();
				      /*calculate the average*/
			        cout << "\nAverage cost: ";
		        	cout << (((float)(ST.GetCost()))/(ST.GetOperation()));
			        cout << " tree accesses/operation\n";
		      }
			    /*no info to return*/
		      else
			        cout << "\nNo cost information available.\n";
}
