/****************************************************************************

                                                           ChakMan Sio
                                                           CSE 12, Fall 2016
                                                           October 3, 2016
                                                           cs12xef
                                                           Assignment Three

File Name:      stack.c
Description:    This program allow user to deal with stack, user can
                try to use push, top, and pop to know how the stack work
								and we use pointer to know whats the index of last used space

 ****************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "stack.h"

#define STACK_POINTER_INDEX (-1)        /* Index of last used space */
#define STACK_SIZE_INDEX (-2)           /* Index of size of the stack */
#define STACK_COUNT_INDEX (-3)          /* Index of which stack allocated */
#define STACK_OFFSET 3  /* offset from allocation to where user info begins */

/* catastrophic error messages */
static const char DELETE_NONEXIST[] = "Deleting a non-existent stack!!!\n";
static const char EMPTY_NONEXIST[] = "Emptying a non-existent stack!!!\n";
static const char INCOMING_NONEXIST[] = 
                        "Incoming parameter does not exist!!!\n";
static const char ISEMPTY_NONEXIST[] = 
                        "Isempty check from a non-existent stack!!!\n";
static const char ISFULL_NONEXIST[] = 
                        "Isfull check from a non-existent stack!!!\n";
static const char NUM_NONEXIST[] = 
                        "Num_elements check from a non-existent stack!!!\n";
static const char POP_NONEXIST[] = "Popping from a non-existent stack!!!\n";
static const char POP_EMPTY[] = "Popping from an empty stack!!!\n"; 
static const char PUSH_NONEXIST[] = "Pushing to a non-existent stack!!!\n";
static const char PUSH_FULL[] = "Pushing to a full stack!!!\n";
static const char TOP_NONEXIST[] = "Topping from a non-existent stack!!!\n";
static const char TOP_EMPTY[] = "Topping from an empty stack!!!\n";
static const char WRITE_NONEXIST_FILE[] = 
                        "Attempt to write using non-existent file pointer!!!\n";
static const char WRITE_NONEXIST_STACK[] = 
                        "Attempt to write to a non-existent stack!!!\n";

/* Debug messages. HEX messages used for negative numbers on the stack. */
static const char ALLOCATED[] = "[Stack %ld has been allocated]\n";
static const char DEALLOCATE[] = "[Stack %ld has been deallocated]\n";
static const char HEXPOP[] = "[Stack %ld - Popping 0x%lx]\n";
static const char HEXPUSH[] = "[Stack %ld - Pushing 0x%lx]\n";
static const char HEXTOP[] = "[Stack %ld - Topping 0x%lx]\n";
static const char POP[] = "[Stack %ld - Popping %ld]\n";
static const char PUSH[] = "[Stack %ld - Pushing %ld]\n";
static const char TOP[] = "[Stack %ld - Topping %ld]\n";

/* static variable allocation */
static int debug = FALSE; /* allocation of debug flag */
static int stack_counter = 0; /* number of stacks allocated so far */

/* Debug state methods */
void debug_off (void) {
        debug = FALSE;
}

void debug_on (void) {
        debug = TRUE;
}

/*--------------------------------------------------------------------------
Function Name:          delete
Description:            This function asks for input and displays output
                        so, the main concept is using if statement to check
												the stack reference and pointer stack. We also 
												need to free the momory after we deleted
Purpose:                delete the stack
Input:                  
    **spp:              values of spp are expected to be a double pointer
		                    to the stack that is to be deleted
return:                 return void 
--------------------------------------------------------------------------*/

/* start of true stack code */
void delete_Stack (Stack ** spp) {
   /* if the stack pointer is null or*/
	 /* or the pointer stack is null*/
   if(spp == NULL || *spp == NULL){
       /* it will print the Delete_NONESIST Error*/
       fprintf(stderr, DELETE_NONEXIST);
			 /* return for the void */
			 return;
   }
   else{
       /*free the menmory*/
       free(*spp-STACK_OFFSET);
   }
	 /* if the debug is true*/
   if (debug == TRUE){
       /* it will print the error message*/
       fprintf(stderr, DEALLOCATE, (long)stack_counter);
			 /* stack_counter decretment*/
       stack_counter--;
   }
}
/*--------------------------------------------------------------------------
Function Name:          empty_stack
Description:            using the if stement to test whether the stack is 
                        empty. if yes, it clear the stack, if not 
												empty_nonexist
Purpose:                clear the stack
Input:                  
    * this_Stack        expected to be a pointer to the stack to be emptied
return                  none
--------------------------------------------------------------------------*/

void empty_Stack (Stack * this_Stack) {
    /* this if statement to check ing the empty and print out error statment*/
    if (this_Stack) {
				/* the stack_pointer_index = -1*/
        this_Stack[STACK_POINTER_INDEX] = -1;
    } 
		else {
				/* print the error nonexit*/
        fprintf(stderr, EMPTY_NONEXIST);
    }

}
/*--------------------------------------------------------------------------
Function Name:          isempty
Description:            using the if statment to check whether the stack is 
                        empty, so i use the pointer index to compare
												if it is emty, return true, not return false
Purpose:                check whether the stack is empty
Input:                  
    * this_Stack        expected to be a pointer to the stack to be checked
return:                 true or false
--------------------------------------------------------------------------*/
    
long isempty_Stack (Stack * this_Stack) {
    /*if the stack is empty */
    if (this_Stack) {
        if (this_Stack[STACK_POINTER_INDEX] == -1) {
				    /*return true*/
            return 1;
        }
        else {
				    /* return false*/
            return 0;
        }
    } else {
				/* and print the error message*/
        fprintf(stderr, ISEMPTY_NONEXIST);
    }
		/* and return true to the function*/
    return 1;
}
/*--------------------------------------------------------------------------
Function Name:          isfull
Description:            I use the if statment to check weather the stack 
                        is full, so i compare between stack + 1 equal 
												the original stack index. Thus we know the 
Purpose:                check weather the stack is full
Input:                  
    *this_Stack         expect to be a pointer to the stack to be checked
return:                 true or false
--------------------------------------------------------------------------*/

long isfull_Stack (Stack * this_Stack) {
    /* this is checking for is the stack full*/
    if (this_Stack) {
				/* this alogorithm is checking weather is full*/
				/*if the stack pointer index+ 1 is equal the stack_size*/
        if ((this_Stack[STACK_POINTER_INDEX]+1) == 
				     this_Stack[STACK_SIZE_INDEX]){
				    /* it will return true to the function*/
            return 1;
        }
				/*else return false*/
        else{
            return 0;
        }
    } else {
				/* and print the error statement*/
        fprintf(stderr, ISFULL_NONEXIST);

    }
		/* return 1 to the function*/
    return 1;
}
/*--------------------------------------------------------------------------
Function Name:          new_Stack
Description:            the new stack function is allocat memory to stack
                        and using the debug to tracking the stack allocated
												pefectly
Purpose:                create a new stack
Input:                  
    stacksize            positive stacksize is used to tell how much 
		                     memonry it can allocated in stack
return:                  stack
--------------------------------------------------------------------------*/

Stack * new_Stack (unsigned long stacksize) {
    /* its for allocating the memory to the stack*/
    Stack* stack = (Stack*)(malloc(((stacksize)+STACK_OFFSET)*
		                sizeof(Stack*)))+STACK_OFFSET;
    /* stack pointer index is negative*/
    stack[STACK_POINTER_INDEX] = -1;
		/* its use for create the stack size*/
    stack[STACK_SIZE_INDEX ] = stacksize;
		/* keep tracking the stack_count_index*/
    stack[STACK_COUNT_INDEX] = ++stack_counter;
    /* if the debug is true*/
    if (debug == TRUE){
				/* print the error statement and */
         fprintf(stderr, ALLOCATED, (long)stack_counter);

    }
    return stack;
		
}
/*--------------------------------------------------------------------------
Function Name:          num_element
Description:            checking weather the stack pointer index = -1
                        return 0 if yes, if not the index will add 1
Purpose:                return the number of element to the stack
Input:                  
    this_Stack          this _Stack expect to be a pointer to the stack
return                  number of elements
--------------------------------------------------------------------------*/

long num_elements (Stack * this_Stack) {
    /* if this is the stack*/
    if (this_Stack) {
				/* if the stack_pointer index = -1 */
        if (this_Stack[STACK_POINTER_INDEX ] == -1) {
				    /* we return the 0 to the function*/
            return 0;
        } else {
				    /* we return the stack_pointer + 1 to the function*/
            return this_Stack[STACK_POINTER_INDEX ] + 1;
        }
    } else {
				/* we print out the error message*/
        fprintf(stderr, NUM_NONEXIST);
    }
		/* retrun the number of element to the stack*/
    return this_Stack[STACK_POINTER_INDEX]+1;
}

/*--------------------------------------------------------------------------
Function Name:          pop
Description:            Using the if statement to check whether the pointer 
                        is pointing to the stack, and print the error message
												everytime we remove stack, we will decrement.
												and I use the *item wheather it is negative or positive
Purpose:                remove item to the stack
Input:
    *this_Stack         the this_Stack expect to be a pointer to the stack 
		                    from which to top
		*item               Removes an item from the top of the stack, and sends 
		                    it back through the output parameter item
return                  true or false
--------------------------------------------------------------------------*/

long pop (Stack * this_Stack, long * item) {
    /* it is for stroe information*/
    int indexOfTop;
		/* if this is not the stack*/
    if (!this_Stack) {
				/* we can not pop out because it is noneist*/
        fprintf(stderr, POP_NONEXIST);
        return 0;
    }
		/*use the isempty to check whether the stack is empty*/
    if (isempty_Stack(this_Stack)) {
				/* pop is empty*/
        fprintf(stderr, POP_EMPTY);
        return 0;
    }
    /* this variable store the pointer index*/
    indexOfTop = this_Stack[STACK_POINTER_INDEX]--;
		/* *item is for store the indexOfTOP*/
    *item = this_Stack[indexOfTop];
		if(debug == TRUE ){
    /* we can use the item to know positive or negative*/
		if (*item<0){
        fprintf(stderr, HEXPOP,this_Stack[STACK_COUNT_INDEX], *item);
    }
		else{
				/* print error message*/
				fprintf(stderr, POP, this_Stack[STACK_COUNT_INDEX],*item);
    }
		}

		return 1;
}

/*--------------------------------------------------------------------------
Function Name:          push
Description:            Using the if statement to check whether the pointer 
                        is pointing to the stack, and print the error message
												everytime we remove stack, we will decrement.
												and I use the *item wheather it is negative or positive
Purpose:                add item to the stack
Input:
    *this_Stack         are expect to be a pointer to the stack which to push
		*item               add an item to the stack, and sends it back throught
		                    the output parameter item
return                  true or false
--------------------------------------------------------------------------*/

long push (Stack * this_Stack, long item) {
   /*this index is used for new element*/
    int indexOfNewElement;
    /* this if statement is checking weather the stack is empty*/
		if (!this_Stack){
				/* print the error message for nonexist*/
        fprintf(stderr, PUSH_NONEXIST);
    }
		/* this is statement is checking weather the stack is full*/
		if (isfull_Stack(this_Stack)){
        fprintf(stderr, PUSH_FULL);
				return 0;
    }
		/* increment is index*/
    this_Stack[STACK_POINTER_INDEX]++;
		/* using the index of new element to store the pointer_index*/
    indexOfNewElement = this_Stack[STACK_POINTER_INDEX];
    this_Stack[indexOfNewElement] = item;

    if(debug == TRUE){
		if (item<0){
         fprintf(stderr, HEXPUSH,this_Stack[STACK_COUNT_INDEX], item);
    }
		else{
				 fprintf(stderr, PUSH, this_Stack[STACK_COUNT_INDEX], item);
    }
		}

    return 1;
}
/*--------------------------------------------------------------------------
Function Name:          top
Description:            i use two if statement to cheack whether the 
                        pointer point to the excatly location, and print
												error meesge. And then use if statement to check 
												the negative and positive
Purpose:                send back the item on the stack through the output 
                        parameter item, but not remove it
Input:                  
    * this_Stack        expected to be a pointer to the stack from which top
		* item              expecter of item to be a pointer to a long which store
		                    the topped item
return                  true or false
--------------------------------------------------------------------------*/

long top (Stack * this_Stack, long * item) {
    /* this is for store the index of top*/   
    int indexOfTop;
		/* if this_stack is false*/
    if (!this_Stack) {
				/* this means the top none exist*/
        fprintf(stderr, TOP_NONEXIST);
        /* return false to the function*/
        return 0;
    }
		/* so call the isempty function to make sure the stack is empty or not*/
    if (isempty_Stack(this_Stack)) {
				/* print the error statement*/
        fprintf(stderr, TOP_EMPTY);
        return 0;
    }
    /* this variable store the pointer index*/
    indexOfTop = this_Stack[STACK_POINTER_INDEX];
    *item = this_Stack[indexOfTop];

		if (debug == TRUE){
		/* if the item <0, it means its negavtive*/
		if (*item<0){
        fprintf(stderr, HEXTOP,this_Stack[STACK_COUNT_INDEX], *item);
    }
		else{
				 /* it is positive*/
				 fprintf(stderr, TOP,this_Stack[STACK_COUNT_INDEX], *item);
    }
		}
    return 1;
}


FILE * write_Stack (Stack * this_Stack, FILE * stream) {

        long index = 0;         /* index into the stack */

        if (this_Stack == NULL) {
                fprintf (stderr, WRITE_NONEXIST_STACK);
                return stream;
        }

        if (stream == NULL) {
                fprintf (stderr, WRITE_NONEXIST_FILE);
                return stream;
        }
                
        if (stream == stderr)
                fprintf (stream, "Stack has %ld items in it.\n",
                        num_elements (this_Stack));

        for (index = STACK_COUNT_INDEX + STACK_OFFSET;
                index < num_elements (this_Stack); index++) {

                if (stream == stderr)
                        fprintf (stream, "Value on stack is |0x%lx|\n",
                                this_Stack[index]);
                else {
                        if (this_Stack[index] < 0)
                                fprintf (stream, "%c ",
                                        (char) this_Stack[index]);
                        else
                                fprintf (stream, "%ld ", this_Stack[index]);
                }
        }

        return stream;
}
