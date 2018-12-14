
/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW7
 * File name: Tree.c
 * Description: We are leaning Tree in this assignment, and 
 *              it can allow we search the name from UCSDSTUDENT
 *              and. we can remove, lookup, and insert it
 */


#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <iostream>
#include "Tree.h"
using namespace std;

static const char ALLOCATE[] = " - Allocating]\n";
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char INSERT[] = " - Inserting ";
static const char TREE[] = "[Tree ";

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

struct TNode {
    Base * data;
    TNode * left, * right, *parent;
    static long occupancy;
    unsigned long hasBeenDeleted;

    // left child's height - right child's height
    long balance;

    // 1 + height of tallest child, or 0 for leaf
    long height;
   
	  /*
		 * Constructor name: TNode
		 * increment the occupancy and allocate memory
		 */
    TNode (Base * element) : data (element), left (0), right (0),
                parent (0), hasBeenDeleted (FALSE), balance (0), height(0) {
      
        occupancy ++;
    }
    /*
		 * Deconstructor name: ~TNode
		 * Delete the TNode data
		 */
    ~TNode (void) {
				delete data;
    }

    ostream & Write (ostream & stream) const {
        stream << "at height:  " << height << "  with balance:  "
                        << balance << "  ";
        return data->Write (stream) << "\n";
    }

    ostream & Write_AllTNodes (ostream & stream) const {
        if (left)
            left->Write_AllTNodes (stream);
        if (!hasBeenDeleted)
            Write (stream);
        if (right)
            right->Write_AllTNodes (stream);
        return stream;
    }

    /*
		 * delete_AllTNodes: free AllTNode memory
		 * description: using the if statement check if the left is not null
		 *              delete it, if right is not null delete it,
		 *              if this is not null delete it
		 */

    void delete_AllTNodes (void) {
        if(left !=NULL){
				     left->delete_AllTNodes();
				}
				if(right != NULL){
				    right->delete_AllTNodes();
				}
				delete this;
    }
};   

// initialization of static data fields of Tree
long TNode :: occupancy = 0;
bool Tree :: debug_on = 0;

/*
 *  Routine Name: Tree:: Set_Debug
 *  File:         Tree.c
 *  Description:  Turn on debug message. turn off/on
 */      
void Tree :: Set_Debug (bool option) {
    debug_on = option;
}

Tree :: Tree (const char * name) : root (0), tree_name (strdup (name))
/***************************************************************************
% Routine Name : Tree :: Tree  (public)
% File :         Tree.c
% 
% Description :  Initializes root pointer to NULL, and occupancy to 0.
***************************************************************************/
{
    // TNode occupancy equal 0
    TNode :: occupancy =0;  
	  if (debug_on){
        cerr<<TREE<<name<<ALLOCATE;
    }
}

Tree :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
{
    // if root is not null
    if (root != NULL){
				// root call the delete_AllTNodes
        root -> delete_AllTNodes();
    }
		delete tree_name;

}  /* end: ~Tree */



/*--------------------------------------------------------------------------
Function Name:          Insert
Description:            If the current is not null, and need to chack whether
                        the element is equal, less than or grether. We also
												need to checked whether it hasbeendeleted
Purpose:                insert element to tree
Input:                  
    element             it is a pointer that expect to be completes to insert
return:                 null and current data
--------------------------------------------------------------------------*/

unsigned long Tree :: Insert (Base * element) {
    // it is a pointer that points to root
    TNode *current = root;
    
		if (debug_on){
        cerr<<TREE<<tree_name<< INSERT << (char*)*element<<"\n";
    }
		// if root is null
    if(!root){
        root = new TNode(element);
    }
		
    else{
        while(1){
				    if (debug_on){
				        cerr<<TREE<<tree_name<<COMPARE<<(char*)*element<<AND <<
								(char*)*current->data << "]"<<"\n";
				    }
				    // duplicate case
            if (*(current->data) == *element){
				        delete current->data;
								// current data = element
				        current->data = element;
								// if current hasBeenDeleted
					      current->hasBeenDeleted = 0;
                return 1;
				    }
				    // if current is less than element
				    else if (*(current->data)<*element){
                if (!current->right){
								    // current right create a new TNode
                    current->right = new TNode(element);
								    current->right ->parent = current;
								    current = current->right;
								    break;
				        }
				        else{
								    // current = right
				            current = current->right;
				        }
				    }
						// this is greater than 
				    else{
				    // if the current's left is NUll
                if (!current->left){
						        current->left = new TNode(element);
								    current->left ->parent= current;
								    // current to left
                    current = current ->left;
								    break;
				        }
						    else{
				            current = current->left;
				        }
				    }
        }
    }
    
    // check whether the current is null and curren parent is not null
		while (current != NULL && current->parent != NULL){
				// for left height
        long leftHeight =-1;
				// for right height
				long rightHeight =-1;
				current = current->parent;
				if(current->left !=NULL){
            leftHeight = current->left->height;
        }
				// if current is not equal null
        if (current ->right !=NULL){
            rightHeight = current ->right->height;
				}
				// check whether left is less than right
				if (leftHeight < rightHeight){
            current->height= rightHeight +1;
				}
				else{
				    // current height = left+1
            current->height = leftHeight +1;
				}
				// balance = left = right
				current->balance = leftHeight - rightHeight;
    }
    return 1;
}


/*--------------------------------------------------------------------------
Function Name:          Lookup
Description:            Use the loop to test whether the current is not equal
                        root, and using hasbeendeleted to mark it to false 
Purpose:                look up the element
Input:                  
    element             it is a pointer, expect to be completes to look up
return:                 null and current data
--------------------------------------------------------------------------*/


const Base * Tree :: Lookup (const Base * element) const {
    TNode*current = root;
    // while current is not equal root
    while (current!= NULL){
        if (debug_on){
            cerr<<TREE<<tree_name<<COMPARE<<(char*)*element<<AND <<
				                                (char*)*current->data << "]"<<"\n";
        }

				// if element equal current data
        if (*element == *(current->data)){
				    // if current hasbeendeleted
				    if ((current->hasBeenDeleted == 1)){
                return NULL;
				    }
				    else{
								// return current data
                return current->data;
				    }
				}
				// if element is less than current data
        else if(*element<*(current->data)){
				    // current = current to left
            current = current->left;
				}
				else{
				    // current = current to right
            current = current->right;
        }
    }
    return NULL;
}

/*--------------------------------------------------------------------------
Function Name:          Remove
Description:            If the current is not null, and need to chack whether
                        the element is equal, less than or grether. We also
												need to checked whether it hasbeendeleted
Purpose:                effectively shifts the elements of the list forward
Input:                  
    element             it is a pointer that expect to be completes to remove
return:                 null and current data
--------------------------------------------------------------------------*/

Base * Tree :: Remove (const Base * element) {
    TNode*current = root;
    // while current is not root
    while (current!= NULL){
        if (debug_on){
            cerr<<TREE<<tree_name<<COMPARE<<(char*)*element<<AND <<
						(char*)*current->data << "]"<<"\n";
        }

				// if element equal current
        if (*element == *(current->data)){
				    if ((current->hasBeenDeleted == 1)){
                return NULL;
				    }
				    else{
								// hasBeenDelated equal 1
								current->hasBeenDeleted = 1;
								// decrement occupancy
								TNode:: occupancy--;
                return current->data;
				    }

				}
				// if element is less tahtn current
        else if(*element<*(current->data)){
				    // current = left
            current = current->left;
				}
				else{
				    // current = right
            current = current->right;
        }
				
    }
		// return null				
    return NULL;
}

ostream & Tree :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
{
        stream << "Tree " << tree_name << "\n" 
				<< "occupancy is " << TNode :: occupancy << " elements.\n";
              
        return (root) ? root->Write_AllTNodes (stream) : stream;
}     /* end: Write */

