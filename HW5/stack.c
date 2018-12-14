/****************************************************************************

                                                           ChakMan Sio
                                                           CSE 12, Fall 2016
                                                           October 3, 2016
                                                           cs12xef
                                                           Assignment Four

File Name:      stack.c
Description:    This program allow user to deal with stack, user can
                try to use push, top, and pop to know how the stack work
								and we use pointer to know whats the index of last used space

 ****************************************************************************/
#include <stdio.h>
#include "list.h"
#include "stack.h"


/*--------------------------------------------------------------------------
Function Name:          delete
Description:            call the delete_List_function
Purpose:                delete the stack
Input:                  
    **spp:              values of spp are expected to be a double pointer
		                    to the stack that is to be deleted
return:                 void
--------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
        delete_List (spp);
}


/*--------------------------------------------------------------------------
Function Name:          isempty
Description:            return isempty_List 
Purpose:                check whether the stack is empty
Input:                  
    * this_Stack        expected to be a pointer to the stack to be checked
return:                 return isempty_List
--------------------------------------------------------------------------*/
    
long isempty_Stack (Stack * this_stack) {
        return isempty_List (this_stack);
}


/*--------------------------------------------------------------------------
Function Name:          new_Stack
Description:            call the new_List function
Purpose:                return this information to the function
Input:                  
		copy_func           copy the information
		delete_func         delete infomation
		write_func          write it to the stream
return                  new_List function
--------------------------------------------------------------------------*/
Stack * new_Stack (void *(*copy_func) (void *),
        void (*delete_func) (void *),
        FILE *(*write_func) (void *, FILE *)) {

        return new_List (copy_func, delete_func, write_func);
}


/*--------------------------------------------------------------------------
Function Name:          pop
Description:            call the remove_List funtion
Purpose:                return information to the function
Input:                  
    * this_Stack        expected to be a pointer to the stack 
return                  remove_List function
--------------------------------------------------------------------------*/


void * pop (Stack * this_stack) {
        return remove_List (this_stack, END);
}


/*--------------------------------------------------------------------------
Function Name:          top
Description:            call the insert funtion
Purpose:                return information to the function
Input:                  
    * this_Stack        expected to be a pointer to the stack 
		* element           for insert in the list
return                  insert function
--------------------------------------------------------------------------*/

long push (Stack * this_stack, void * element) {
        return insert (this_stack, element, END);
}

/*--------------------------------------------------------------------------
Function Name:          top
Description:            call the view funtion
Purpose:                return infomation to the function
Input:                  
    * this_Stack        expected to be a pointer to the stack 
return                  view function
--------------------------------------------------------------------------*/

void * top (Stack * this_stack) {
        return view (this_stack, END);
}

/*--------------------------------------------------------------------------
Function Name:          write_stack
Description:            call the write_list funtion
Purpose:                return infomation to the function
Input:                  
    * this_Stack        expected to be a pointer to the stack from which top
    * stream            put the informtion to the file
return                  write_List function
--------------------------------------------------------------------------*/
FILE * write_Stack (Stack * this_stack, FILE * stream) {
        return write_List (this_stack, stream);
} 
