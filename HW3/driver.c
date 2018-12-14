/****************************************************************************

                                                           ChakMan Sio
                                                           CSE 12, Fall 2016
                                                           October 3, 2016
                                                           cs12xef
                                                           Assignment Three

File Name:      driver.c
Description:    This program allow users pick option to control stack
                users can pick pop, push, or top to know whats 
								the stack really work.

 ****************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"
#include "stack.h"
/*(1)0X603010
 *(2)0X603028
 *(3)heap
 *(4)0X7fffffff9a8
 *(5)0X60303028
 *(6)0X603010
 *(7)its same*/



int main (int argc, char * const * argv) {

        Stack * main_Stack = 0;         /* the test stack */
        unsigned long amount;        /* numbers of items possible go on stack */
        long command;                   /* stack command entered by user */
        long item = 0;                  /* item to go on stack */
        char option;                    /* the command line option */
        long status;                    /* return status of stack functions */
        
        /* initialize debug states */
        debug_off ();

        /* check command line options for debug display */
        while ((option = getopt (argc, argv, "x")) != EOF) {
                
                switch (option) {
                        case 'x': debug_on (); break;
                }
        }

        while (1) {
                command = 0;            /* initialize command, need for loops */
                writeline ("\nPlease enter a command:", stdout);
                writeline ("\n\t(a)llocate, (d)eallocate, ", stdout);
                writeline ("p(u)sh, (p)op, (t)op, (i)sempty, (e)mpty, ",stdout);
                writeline ("\n\tis(f)ull, (n)um_elements, (w)rite to stdout, "
                                                                , stdout);
                writeline ("(W)rite to stderr.\n", stdout);
                writeline ("Please enter choice:  ", stdout);
                command = getchar ();
                if (command == EOF)     /* are we done? */
                        break;
                clrbuf (command);       /* get rid of extra characters */

                switch (command) {      /* process commands */

                /* YOUR CODE GOES HERE */
                case 'a':
                        writeline("Please enter the number of objects", stdout);
												writeline("to be able to store: ", stdout);
                        amount= decin();
												
												clrbuf(0);
                        /* if the main stack is not equal 0*/
												if (main_Stack != 0){
												    /* delete the delete*/
                            delete_Stack(&main_Stack);
												}
												   /* add the new stack*/
											     main_Stack = new_Stack(amount);
                        
                        break;
                    
                case 'd':
								        /* delete_stack*/
                        delete_Stack(&main_Stack);
												/* call the writeline function*/
                        writeline("Stack has been deleted.\n", stdout);
                        break;
                    
                case 'e':
                        empty_Stack(main_Stack);
                        writeline("Stack is empty.\n", stdout);
                        break;
                        
                case 'f':               /* isfull */
                        if (isfull_Stack (main_Stack))
                                writeline ("Stack is full.\n",stdout);
                        else
                                writeline ("Stack is not full.\n", stdout);
                        break;

                case 'i':               /* isempty */
                        if (isempty_Stack (main_Stack))
                                writeline ("Stack is empty.\n", stdout);
                        else
                                writeline ("Stack is not empty.\n", stdout);
                        break;

                case 'n':               /* num_elements */
                        writeline ("Number of elements on the stack is:  ",
                                                                    stdout);
                        decout (num_elements (main_Stack));
                        newline ();
                        break;

                case 'p':               /* pop */
                        status = pop (main_Stack, &item);
                        if (! status)
                                fprintf (stderr,"\nWARNING:  pop FAILED\n");
                        else {
                                writeline (
                                        "Number popped from the stack is:  ",
                                                                    stdout);
                                decout (item);
                                newline ();
                        }
                        break;

                case 't':               /* top */
                        status = top (main_Stack, &item);
                        if (! status)
                                fprintf (stderr,"\nWARNING:  top FAILED\n");
                        else {
                                writeline (
                                        "Number at top of the stack is:  ",
                                                                    stdout);
                                decout (item);
                                newline ();
                        }
                        break;

                case 'u':               /* push */
                        writeline (
                                "\nPlease enter a number to push to stack:  ",
                                                                    stdout);
                        item = decin ();
                        clrbuf (0);     /* get rid of extra characters */
                        status = push (main_Stack, item);
                        if (! status)
                                fprintf(stderr,"\nWARNING:  push FAILED\n");
                        break;

                case 'w':               /* write */
                        writeline ("\nThe Stack contains:\n", stdout);
                        write_Stack (main_Stack, stdout);
                        break;

                case 'W':               /* write */
                        writeline ("\nThe Stack contains:\n", stdout);
                        write_Stack (main_Stack, stderr);
                        break;
                }

                if (item == EOF) /* check if done */
                        break;
        }

        if (main_Stack)
                delete_Stack (&main_Stack);     /* deallocate stack */
        newline ();
        return 0;
}

