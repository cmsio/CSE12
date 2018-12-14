/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW8
 * File name: Tree.c
 * Description: We are leaning Tree in this assignment, and 
 *              it can allow we search the name from UCSDSTUDENT
 *              and. we can remove, lookup, and insert it. We also
 *              use the recursion to implement remove and insert.
 */


#include <cstdlib>
#include <string>
#include "Tree.h"
using namespace std;

// messages
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char INSERT[] = " - Inserting ";
static const char REPLACE[] = " - Replacing ";
static const char UPDATE[] = " - Updating ";

template <class Whatever>
int Tree<Whatever>::debug = 0;

#ifndef TRUE

#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define THRESHOLD 2

template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

template <class Whatever>
/*--------------------------------------------------------------------------
 *strut Name:             TNode
 *Description:            It is use for implements the node of the binary  
                          tree (balance). Every node has two children, the left 
                                              child that pointing to TNode<Whatever>, and the right 
                                              child that pointing to TNode<Whatever>
 *Data Fields:    
     balance:             it is use for balance the tree
         data:                it is for share the data
         height:              it is for the height for every node
         left:                the left child
         occupancy:           keep tracking the occupancy
         right:               the right child
         tree_count:          it is for count the tree

 *functions:
 *    delete_AlITNodes    delete all the children of the current node
 *    Replaceandremovemin Call when delete two children
 *    TNode's Remove      Remove the matching data from binary tree
 *    SetHeightAndBalace  Updates the height and balance of the node
 *    TNode's Insert      insert an element into the tree
 *    Tree's Insert       insert an element into the tree
 *    Tree's Lookup       look up the element
 *    Tree's Remove       remove element form the tree
 * -------------------------------------------------------------------------*/
struct TNode {
        long balance;
        Whatever data;
        long height;
        TNode<Whatever> * left;
        long & occupancy;
        TNode<Whatever> * right;
        unsigned long & tree_count;
/*--------------------------------------------------------------------------
Constructor  Name:                     TNode
Description:                           increment occupanacy and alllocation
                                       memory  
Purpose:                               Call when allocating a TNode
Input:                  
    element                            expected to be the data to be stored 
                                           in the TNode    
        parentTnode                        expected to be a reference to the parent 
                                           of the TNode about to be created
Data Fields:
    balance(0)                         initialize the balance t 0;
        data(element)                      set data to element
        height(0)                          set height to 0
        left(0)                            set left to 0
        right(0)                           set right to 0
        occupancy(parentTNode.occupancy)   occupnact store the parentTNode call 
        right(0)                           set right to 0
        tree_count(parentTNode.tree_count) count the table
return:                                void
-----------------------------------------------------------------------------*/
        TNode (const Whatever & element, Tree<Whatever> & theTree)
                : balance (0), data (element), height (0), left (0), 
                occupancy (theTree.occupancy), right (0), 
                tree_count (theTree.tree_count) {
                    // increment the occupancy
            occupancy++;
        }

/*--------------------------------------------------------------------------
Constructor  Name:                     TNode
Description:                           increment occupanacy and alllocation
                                       memory  
Purpose:                               Call when allocating a TNode
Input:                  
    element                            expected to be the data to be stored 
                                           in the TNode    
        parentTnode                        expected to be a reference to the parent 
                                           of the TNode about to be created
Data Fields:
    balance(0)                         initialize the balance t 0;
        data(element)                      set data to element
        height(0)                          set height to 0
        left(0)                            set left to 0
        right(0)                           set right to 0
        occupancy(parentTNode.occupancy)   occupnact store the parentTNode call 
        right(0)                           set right to 0
        tree_count(parentTNode.tree_count) count the table
return:                                void
--------------------------------------------------------------------------*/

        
        TNode (const Whatever & element, TNode<Whatever> & parentTNode)
        : balance (0), data (element), height (0), left (0), 
                occupancy (parentTNode.occupancy), right (0), 
                tree_count (parentTNode.tree_count) {

                    // increment occupancy
            occupancy ++;
        }

/*--------------------------------------------------------------------------
Destrucor  Name:          ~TNode
Description:              decrement occupancy and dealloate memeory
Purpose:                  Call when deallocating a TNode
Input:                    void
return:                   void
--------------------------------------------------------------------------*/

        ~TNode (void) {
                    // decrement the occupancy
                    occupancy--;
        }

/*--------------------------------------------------------------------------
Function Name:          delete_AllTNodes
Description:            if left is not empty delete left, if right is not 
                        empty, delete right, and delete this
Purpose:                post_order traversal delete all tnode
Input:                  void
return:                 void
--------------------------------------------------------------------------*/

        void delete_AllTNodes (void) {
                    // if left is not equal NULL
            if (left != NULL){
                left->delete_AllTNodes();
                    }
                        // If right is not equal null
                        if(right != NULL){
                right->delete_AllTNodes();
                    }
                        // delete current node
                        delete (this);
        }

        unsigned long Insert (const Whatever & element, 
                              TNode<Whatever> *& PointerInParent);

        // OPTIONAL TNode :: Lookup => uncomment if implementing recursively
        // unsigned long Lookup(Whatever & element) const;

/*--------------------------------------------------------------------------
Function Name:          ReplaceAndRemoveMin
Description:            I first check whether left is exist, if it is exist
                        we call he ReplaceAndRemoveMin and 
                        SetHeightAndBalance function. If not, the
                        PointerInParent is equal right, and delete it
Purpose:                Remove a node with two children, TNode with the minimum
                        TNode in its right subtree
Input:                  
    targetTNode         expent to be a reference to TNode remove two children
    PointerInParent     expect to be a reference to the TNode opointer in the
                        parent TNode to get the current TNode
return:                 void
--------------------------------------------------------------------------*/

        void ReplaceAndRemoveMin (TNode<Whatever> & targetTNode, 
                TNode<Whatever> *& PointerInParent){
                
                    // debug message
                    if (Tree<Whatever>::debug){
                cerr<<"["<<TREE << tree_count<< REPLACE<< 
                                (const char*) data<<"]\n";
                    }
            // if it is left
                    if(left){
                                // left call the replaceandremovemin function
                                left->ReplaceAndRemoveMin(targetTNode, left);
                                SetHeightAndBalance(PointerInParent);
                    }
                    else{
                                // targetTNodedata euqal data
                        targetTNode.data= data;
                                PointerInParent = right;
                                delete (this);
                    }
        }

/*--------------------------------------------------------------------------
Function Name:          TNode's Remove
Description:            If the current is not null, and need to chack whether
                        the element is equal, less than or grether. We also
                                                need to checked whether it hasbeendeleted
Purpose:                effectively shifts the elements of the list forward
Input:                  
    elementTNode        expect to be reference indentisfy the current 
                            element to remove
        fromSHB             expect to be true or false
        POinterInParent     expected to be a reference to the TNode pointer to 
                            parent
return:                 return true or false
--------------------------------------------------------------------------*/

        unsigned long Remove (TNode<Whatever> & elementTNode, 
                        TNode<Whatever> *& PointerInParent,
                long fromSHB = FALSE){
            
            if (Tree<Whatever>::debug){
                cerr<<TREE << tree_count<<COMPARE<<
                                (const char*) elementTNode.data<<AND<<
                        (const char*)data << "]"<<"\n";
            }

            if (elementTNode.data == (data)){
                                // elementTNode = data
                                elementTNode.data = data;
                // want to check there is two children
                                if (left !=NULL && right != NULL){
                                    // right call the RARM
                    right->ReplaceAndRemoveMin(*this, right);
                                        SetHeightAndBalance(PointerInParent);
                }
                // if two children are not exist
                                else if (!(left) && !(right)){
                                    delete(this);
                    PointerInParent = NULL;  
                                }
                // if only have left								
                                else if (left){
                                    // pointerInparent equal left
                    PointerInParent= left ; 
                                        delete (this);
                }
                                // if only have right child
                                else if (right){
                                    // PointerInParenet equal right
                                    PointerInParent = right;
                                        delete (this);
                }
                                else {
                    PointerInParent = this;
                                }
                                // return true
                                return 1;
                    }
           
                    else{
                                // if elementTNode is less thatn data
                                if(elementTNode.data < (data)){
                                    if(left){
                                        // remove left
                        left->Remove(elementTNode, left);
                                    }
                                    else{
                        return 0;
                                    }
                        }
                else{
                                    // if it is right
                                    if (right){
                                        // remove right
                        right->Remove(elementTNode, right);
                                    }
                                    else{
                        return 0;
                                    }
                }
        
                            if (!fromSHB){
                                    // call setheightandbalance
                    SetHeightAndBalance(PointerInParent);
                                }
                    }
            return 1;
        }
                
/*--------------------------------------------------------------------------
Function Name:          SetHeightAndBalance
Description:            if it is left is exist, left_height equal left point
                        to height, if it is right, right height euqal
                                                right point to height
Purpose:                Updated the height and balance of the current TNode  
Input:                  
    PointerInParent     expext to be a reference to the TNode pointer in parent
return:                 void               
--------------------------------------------------------------------------*/

        void SetHeightAndBalance (TNode<Whatever> *& PointerInParent) {
                    // this variable is order to get the right's height
                    long right_height =-1;
                        // this variable is order to get the left's height
                long left_height = -1;

            if (Tree<Whatever>::debug){
                cerr<<TREE << tree_count<< UPDATE<< 
                                (const char*) data<<"]\n";
                    }
            // if left exist
                if (left){
                left_height = left -> height;
            }
                // if right exist
                if (right){
                right_height = right->height;
            }
                        // if left height is less thatn right
                if (left_height < right_height){
                height = right_height+1;
            }
                else {
                height = left_height+1;
            }
                        
                        // calculate balance
              balance = left_height - right_height;
                            // if the balance is greather than 2
                    if (abs(balance) > THRESHOLD){
                               
                                    TNode<Whatever> elementTNode(data, *this);
                                    // cal the remove function 
                                    this->Remove(elementTNode, PointerInParent, true);
                    PointerInParent->Insert(elementTNode.data,PointerInParent);
                }
                }

        ostream & Write_AllTNodes (ostream & stream) const {
            if (left)
                left->Write_AllTNodes (stream);
                stream << *this;
            if (right)
                right->Write_AllTNodes (stream);
                return stream;
        }
};
/*--------------------------------------------------------------------------
Function Name:          Tree<Whatever> ::Set_Debug_On
Description:            just set debug on
Purpose:                Set on the debug
Input:                  
    element             void
return:                 void
--------------------------------------------------------------------------*/

template <class Whatever>
void Tree<Whatever> ::Set_Debug_On(){
    debug = 1;
}

/*--------------------------------------------------------------------------
Function Name:          Tree<Whatever> ::Set_Debug_Off
Description:            just set debug is false 
Purpose:                Set off the debug
Input:                  
    element             void
return:                 void
--------------------------------------------------------------------------*/

template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off(){
    debug =0;
}


/*--------------------------------------------------------------------------
Function Name:          TNode<Whatever>::Insert
Description:            I first check if the element is equal data, then check
                        whether the element is less than data. If it is, we
                                                should have two cases, first one is left doesnt 
                                                exist, then create a new one, second is right 
                                                doesnt exist, and create a new on.
Purpose:                Inserts and element into the binary tree
Input:                  
    element:            expect to be a data to store in the TNode
        PointerInParent:    expect to be a reference to the TNode pointer in the 
                            parenet TNode
return:                 True or False
--------------------------------------------------------------------------*/

template <class Whatever>
unsigned long TNode<Whatever> :: Insert (const Whatever & element, 
                                         TNode<Whatever> *& PointerInParent) {
    if (Tree<Whatever>::debug){
        // debug message
        cerr<<TREE << tree_count<<COMPARE<<(const char*) element<<AND<<
                (const char*)data << "]"<<"\n";
    }

    // if element is equal data
    if (element == data){
        data = element;
                 if (Tree<Whatever>::debug){
                     cerr<<TREE<<tree_count<<INSERT<< (const char*)element<<"]\n";
         }
                // return true
                return 1;
    }
    // if the element is less than data
        else if (element< data){
                // if left is not exist
                if (!left){
                    left = new TNode<Whatever>(element, *this);
                    if (Tree<Whatever>::debug){
                        cerr<<TREE<<tree_count<<INSERT<< (const char*)element<<"]\n";
                    }

                }

                // if its exist, recursive call
                else {
            left ->Insert(element, left);
                }
    }
    else{
                // if right is not exist
                if(!right){
                    // create a new TNode
            right = new TNode<Whatever>(element, *this);
                    if (Tree<Whatever>::debug){
                        cerr<<TREE<<tree_count<<INSERT<< (const char*)element<<"]\n";
                    }

                }
                else {
                    // recursive call
            right ->Insert(element, right);
                }
    }
    // call the setheightandbalance
    SetHeightAndBalance(PointerInParent);

        return true;
}


template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
        stream << "at height:  :" << nnn.height << " with balance:  "
                << nnn.balance << "  ";
        return stream << nnn.data << "\n";
}

/*--------------------------------------------------------------------------
Function Name:          TNode<Whatever>::Insert
Description:            if root is empty, then create a new Node. If it is
                        not empty, return root call insert function
Purpose:                Insert an element into the binary tree.
Input:                  
    element             expect to be the data stored in the TNode
return:                 true or false
--------------------------------------------------------------------------*/

template <class Whatever>
unsigned long Tree<Whatever> :: Insert (const Whatever & element) {
    // if root is empty
    if(root == NULL){
                // create a new TNode
        root = new TNode<Whatever>(element, *this);
    }
        else{
                // root call the Insert function
        return (root->Insert(element, root));
    }
    return 0;
}

/*--------------------------------------------------------------------------
Function Name:          Tree<Whatever>::Lookup
Description:            I use while loop to implement this function, first
                        , we need to check whether the current is not empty
                                                if it is we should have four cases, equal, less than
                                                , and greather than to check the current data and 
                                                element
Purpose:                Searches for an element in the Tree
Input:                  
    element             expect to be the data stored in the TNode
return:                 true or false
--------------------------------------------------------------------------*/

template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {
     TNode<Whatever>*current = root;
    // while current is not equal root
    while (current!= NULL){
        if (Tree<Whatever>::debug){
            cerr<< "["<<"Tree" << tree_count<<COMPARE<<(char*)&element<<" and "
                                            <<(const char*)current->data <<"]"<<endl;
                }
                // if element equal current data
        if (element == current->data){
            element = current->data;
                        return true;
                }
                // if element is less than current data
        else if(element<current->data){
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
Function Name:          Tree<Whatever>::Remove
Description:            we need to check whether the root is not empty,
                        if not empty, we can remove it
Purpose:                Removes an element from the tree
Input:                  
    element             element are expected to be the the data stroe in TNode
return:                 false or store_data
--------------------------------------------------------------------------*/

template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {
    // this variable is for store the data from root call remove function
    int store_data;
        // if root is not empty
    if (!root){
        return 0;
    }
        // create a new TNode to store the data
        TNode<Whatever> current( element,*this);
        // it use for store data
    store_data = root ->Remove(current, root);
    element = current.data;
    return store_data;
}
                                
/***************************************************************************
% Routine Name : Tree<Whatever> :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

template <class Whatever>
Tree<Whatever> :: ~Tree (void)
{
    // this one is debug message
    if (Tree<Whatever>::debug){
        cerr<< TREE << tree_count<<DEALLOCATE;
    }
        // if root exist
    if (root){
        this->root->delete_AllTNodes();
    }
}
/***************************************************************************
% Routine Name : Tree<Whatever> :: Write (public)
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

template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
{
        stream << "Tree " << tree_count << ":\n"
                << "occupancy is " << occupancy << " elements.\n";

        return (root) ? root->Write_AllTNodes (stream) : stream;
}
