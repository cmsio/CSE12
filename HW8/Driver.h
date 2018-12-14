/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW8
 * File name: Driver.h
 * Description: In this function, My tree can use access UCSDStudent function 
 *              for example, we can use their name, equal function, and less 
 *              than function
 */


#ifndef DRIVER_H
#define DRIVER_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;
/*--------------------------------------------------------------------------
Class Name:             UCSDStudent
Description:            My tree can access UCSDStudnet function, for example
                        we can overwrite name, equal function, and less than 
												function. we also can use the copy constructor
												and normal constructor
Data Fields:
        name[20]        get the student name with size 20
		    studentnum      student name
Public Functions:
    UCSDStudent         copy constructor
		UCSDStudent         nomal constructor
    operator            overwrite the name
		operator            overwrite equal 
    operator            overwrite less than 
--------------------------------------------------------------------------*/

class UCSDStudent {
        friend ostream & operator << (ostream &, const UCSDStudent &);
        char name[20];
        long studentnum;
public:
/*--------------------------------------------------------------------------
Function Name:          UCSDStudent
Description:            copy the constructor
Purpose:                copy the exist object
Input:                  
   nm                   student name
	 val                  student number
return:                 void
--------------------------------------------------------------------------*/

    UCSDStudent (char * nm, long val = 0) : studentnum (val) {  
                strcpy (name, nm);  
    }  
/*--------------------------------------------------------------------------
Function Name:             UCSDStudent
Description:               UCSD Student constructor
Purpose:                   this construct UCSD Student's object
Input:                     
    UCSDStudent & student  passing student reference
return:                    void
--------------------------------------------------------------------------*/

    UCSDStudent (const UCSDStudent & student) {
                strcpy (name, student.name);
								studentnum = student.studentnum;
    }
/*--------------------------------------------------------------------------
Function Name:          operator
Description:            get the name 
Purpose:                in order to let tree.c to implement
Input:                  void
return:                 name
--------------------------------------------------------------------------*/

		operator const char * (void) const {  
        return name;  
    }  
/*--------------------------------------------------------------------------
Function Name:          operator
Description:            get the result of comparism
Purpose:                Overwrite in the Tree.c
Input:                  
    UCSDStudnet&bbb     the object to compare with the current one
return:                 !strcmp(name, bbb)
--------------------------------------------------------------------------*/

    long operator == (const UCSDStudent & bbb) const {  
        return ! strcmp (name, bbb);  
    }
/*--------------------------------------------------------------------------
Function Name:          operator
Description:            get the result of comparism
Purpose:                Overwrite in the Tree.c
Input:                  
    UCSDStudnet&bbb     the object to compare with the current one
return:                 (strcmp (name, bbb) < 0) ? 1 : 0; 
--------------------------------------------------------------------------*/

    long operator < (const UCSDStudent & bbb) const {  
        return (strcmp (name, bbb) < 0) ? 1 : 0;  
    }  
};

#endif
