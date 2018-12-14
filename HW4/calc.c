/****************************************************************************

                                                           ChakMan Sio
                                                           CSE 12, Fall 2016
                                                           October 19, 2016
                                                           cs12xef
                                                           Assignment Four

File Name:      calc.c
Description:    This program allow users calculate the number base on 
                eval and intopose. We furst use eval to evalate 
								which one is operator, and which one is operand

 ****************************************************************************/


#include <ctype.h>
#include <stdio.h>
#include "calc.h"
#include "mylib.h"
#include "stack.h"

#define CHARACTER(word) ((char) ((word) & 0x000000FF))
#define INDEX(word) (((word) & 0x0000FF00) >> 8)
#define PRIORITY(word) ((word) & 0x0000FE00)
#define NINE '9'
#define HEX_VALUE 0x8000000000000000
#define INDEXS 8

static char operators[] = "()+-*/^ !";

static long add (long, long);
static long divide (long, long);
static long exponent (long, long);
static long fact (long, long);
static long mult (long, long);
static long setupword (int);
static long sub (long, long);

static long (*functions[]) (long, long) =
    { NULL, NULL, add, sub, mult, divide, exponent, NULL, fact };


/*--------------------------------------------------------------------------
Function Name:          eval
Description:            So, first one, i keep tracking whether the stack
                        is empty, if not i can pop to stack1, and push 
												it to stack 2. while stack 2 is not empty
												pop the digit from stack 2. if the digit greater
												than 0, push to stack 1, and then i need to 
												call the function. Finally, i need to delete 
												stack and empty stack
Purpose:                evalate the mathematics expression from posfix
                        notation
Input:                  
    *stack1:            it is used to stroe the opeatorand 
return:                 result
--------------------------------------------------------------------------*/

long eval (Stack * stack1) {
    /* for the operands and opeator*/
		/* the result is for return*/
		/* digit is for record the information*/
    long op1,op2,result,digit;
		/* create a location stack 2 that point to stack*/
    Stack * stack2 = new_Stack(BUFSIZ);

		/* while stack one is not empty*/
    while (!isempty_Stack(stack1)){
				/* pop the stuff from stack1*/
		    pop (stack1, &digit);
				/* push it to the stack 2*/
        push (stack2, digit);
    }
    /* while stack two is not empty*/
    while (!isempty_Stack(stack2)){
       /* pop the digit to stack 2*/
       pop (stack2, &digit);
			 /* if the digit is greater than 0*/
			 if (digit >0){
				  /* push the digit to stack 1*/
          push (stack1, digit);
       }
       else{
          /* pop it to the stack 1*/
          pop (stack1, &op1);
					/* if the index digit is not equal 8*/
				  if(INDEX(digit) != INDEXS){
				     /*pop the operator to stack 1*/
             pop(stack1,&op2);
				  }
          /* this variable stote whats words in the function*/
				  result =functions[INDEX(digit)](op1,op2);
				  /* push the resut to the stack 1*/
          push(stack1, result);
       }		
    }
		/* delete the stack 2*/
		delete_Stack(&stack2);
		/* empty the stack*/
		empty_Stack(stack1);
		/* return the result to the function*/
		return result;
}

/*--------------------------------------------------------------------------
Function Name:          intopost
Description:            while the character is not equal newline return eof
                        if the character is equal blank fget c for handling
												when user type blank. when the user type open space
												it will push the setupwrod to stack2, so i still
												need to check whether the stack is empty, and keep
												pop stuff and push stuff
Purpose:                convert infix to the postfix
Input:                  
    *stack1             it is used for calculate the actually number
return:                 return true 
--------------------------------------------------------------------------*/

long intopost (Stack * stack1){
    /* create a local stacks for store operator*/
    Stack * stack2;
    /* this variable is use for pop and push 
		 * the operator and operandt*/
    long digit =0;
		/* this variable allow users to enter the character*/
		long character;
			/* used to compare the top in the stack*/
		long topval = 0;
		/* used to compare for the priority*/
		long store_character;
    stack2 = new_Stack(BUFSIZ);
    
    /* get the character*/
		character = fgetc (stdin);

		
		/* while the character is not equal new line*/
		while (!(character == '\n')){
        /* if character = end of line*/
				if (character == EOF){
           /* return EOF to the function*/
				   delete_Stack(&stack2);
           return EOF;
				}

        /* if the character equal blank*/
				if (character == ' '){
				    /* handle for the blank case*/
				    character = fgetc(stdin);
				    /* ignore it*/
				    continue;
				}
        /* if the characters are between 0 to 9*/
				if (isdigit(character)){
				    /* character to put back*/
				    ungetc (character, stdin);
            /* push the stack1 to the decin*/
            push(stack1, decin());
        }
        /* if the character equal the open parenthesis*/
				else if(character == '('){
				    /* push it to the stack2*/
				    push (stack2,setupword(character));
				}
				/* if the character equal the close parenthesis*/
				else if (character == ')'){
				    /* is the stack is not empty*/
						if(!isempty_Stack(stack2)){
								/* pop store_character to stack 2*/
				        pop(stack2, &store_character);
						}
				    while (CHARACTER(store_character) != '('){
                /* if the stack is not full*/
				        if(!isfull_Stack(stack1)){
								    /*push the store_character to stack 1*/
				            push(stack1, store_character);
				        }
				        /* if the stack 2 is not empty*/
				        if(!isempty_Stack(stack2)){		
								    /* pop the store_character to stack 2*/
				            pop(stack2, &store_character);
				        }
            }
				}
				else {
				    /* while the stack2 is not empty*/
				    if (!isempty_Stack(stack2)){
               /*call the top function*/
               top(stack2, &topval);
				    }
            /* while the stack2 priority is greater than the setupword 
				     * function*/
            while(!isempty_Stack(stack2) && PRIORITY(topval) > 
				        PRIORITY(setupword(character))){
								/* pop the digit from stack*/
								pop (stack2, &digit);
								/* push the digit to stack1*/
				        push (stack1, digit);
                /* if the stack 2 is not empty*/
				        if (!isempty_Stack(stack2)){
                   /*call the top function*/
                   top(stack2, &topval);
				        }
				    }
				    /* push the word to stack2*/
            push (stack2, setupword(character));
        }
				/* character call the fgetc function*/
        character = fgetc (stdin);
    }
		/* while stack2 is not empty*/
		while (!isempty_Stack(stack2)){
        /* pop the character to the stack 2*/
        pop (stack2,&character);
			  /* push the character to stack 1 */
			  push (stack1,character);
    }
		/* delete the stack */
		delete_Stack(&stack2);
		/* return true to the function*/
		return 1;
}


static long add (long augend, long addend) {
    return augend + addend;
}

static long divide (long divisor, long dividend) {
    return dividend / divisor;
}

/*--------------------------------------------------------------------------
Function Name:          exponent
Description:            I just use the for loop to go over the size
                        and then result times base
Purpose:                get the exponent number
Input:                  
    power:              this is for store power
		base:               this is for store base
return:                 return result
--------------------------------------------------------------------------*/


static long exponent (long power, long base) {
  /* this varaible how many times need to loop*/
  long k;
	/* create a result =1*/
	long result =1;
	/* loop from 0 to less than power case*/
	for (k =0; k<power;k++){
      /* result = result times base*/
      result = result*base;
   }
	 /*return the result to function*/
	 return result;
}

/*--------------------------------------------------------------------------
Function Name:          fact
Description:            if xxx is euql to be a base case return 1
                        else return xxx*fact(xxx-1,ignored)
Purpose:                get the fact number
Input:                  
    xxx:                this is a number to cal the result
return:                 return xxx*fact(xxx-1,ignored)
--------------------------------------------------------------------------*/


static long fact (long xxx, long ignored) {
     /* if the number euqal 1, it will stop recursion*/
     if (xxx==1){
				/*return 1*/
				return 1;
     }
		 else
				/* if not it will call the facttin*/
				return xxx*fact(xxx-1,ignored);
}

static long mult (long factorx, long factory) {
    return factorx * factory;
}



/*--------------------------------------------------------------------------
Function Name:          setupword
Description:            while is 1, if the character is not euql the 
                        operators index, increment the index, else break
												and return the hex value to the function
Purpose:                for set up the word
Input:                  
    character:          its used for compared with the operator index
return:                 result
--------------------------------------------------------------------------*/


static long setupword (int character) {
	   /* creat the index euql zero to increment*/
     int index = 0;
		 /* while its equal 1*/
		 while(1){
       /* if the character is not equal the operators*/
       if (character != operators[index]){
				 /* incretment*/
         index++;
       }
			 /* if not, break*/
			 else
				 break;
     }
		 /* and return the hex value to the setupword*/
		 return HEX_VALUE| index<<8 | character;
}

static long sub (long subtrahend, long minuend) {
    return minuend - subtrahend;
}

