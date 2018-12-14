/****************************************************************************

                                                           ChakMan Sio
                                                           CSE 12, Fall 2016
                                                           October 3, 2016
                                                           cs12xef
                                                           Assignment Five

File Name:      list.c
Description:    This assigment allow me to deal with linked list, this 
                assigment including insert, remove, reserve linked list,
								and view. i can practice more about pointer and free 
								memory

1. end: 1
2. Node 1 data 30
3. Node 2 pre 3
4  Node 1 next 2
5. Node 2 data 40
6. Node 2 pre; 1
7. Node 2 next; 3
8. Node 3 data: 50
9. Node 3 pre: 2
10 Node 3 next: 1
****************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "list.h"

typedef struct Node {
				struct Node * pre;      /* how to access the prior Node */
				struct Node * next;     /* how to access the next Node */
				void * data;            /* the data to store */
} Node;

typedef struct List {
				Node * end;             /* the end of the list */
				long list_count;        /* which list is it */
				long occupancy;
				void *(*copy_func) (void *);
				void (*delete_func) (void *);
				FILE *(*write_func) (void *, FILE *);
} List;

/* private Node function declarations */
static long check_to_go_forward (List * this_list, long where);
static void delete_Node (Node **, void (*delete_func) (void *));
static Node * find_location (List * this_list, long where);
static Node * insert_Node (Node *, void *, void *(*copy_func) (void *));
static Node * new_Node (void *, void *(*copy_func) (void *));
static void * remove_Node (Node *);
static void * view_Node (Node *);
static FILE * write_Node (Node *, FILE *, FILE *(*write_func) (void *, FILE *));

/* catastrophic error messages */
static const char ADNEXT_NONEXIST[] =
"Advance next from non-existent list!!!\n";
static const char ADNEXT_EMPTY[] =
"Advance next from empty list!!!\n";
static const char ADPRE_NONEXIST[] =
"Advance pre from non-existent list!!!\n";
static const char ADPRE_EMPTY[] =
"Advance pre from empty list!!!\n";
static const char CHECK_NONEXIST[] =
"Checking direction on non-existent list!!!\n";
static const char DELETE_NONEXIST[] =
"Deleting from non-existent list!!!\n";
static const char DELETE_NONEXISTNODE[] =
"Deleting a non-existent node!!!\n";
static const char ISEMPTY_NONEXIST[] =
"Is empty check from non-existent list!!!\n";
static const char INSERT_NONEXIST[] =
"Inserting to a non-existent list!!!\n";
static const char REMOVE_NONEXIST[] =
"Removing from non-existent list!!!\n";
static const char REMOVE_EMPTY[] =
"Remove from empty list!!!\n";
static const char VIEW_NONEXIST[] =
"Viewing a non-existent list!!!\n";
static const char VIEW_NONEXISTNODE[] =
"Viewing a non-existent node!!!\n";
static const char VIEW_EMPTY[] =
"Viewing an empty list!!!\n";
static const char WRITE_NONEXISTFILE[] =
"Writing to a non-existent file!!!\n";
static const char WRITE_NONEXISTLIST[] =
"Writing from a non-existent list!!!\n";
static const char WRITE_MISSINGFUNC[] =
"Don't know how to write out elements!!!\n";
static const char WRITE_NONEXISTNODE[] =
"Writing from a non-existent node!!!\n";

/* debug messages */
static const char ADNEXT[] = "[List %ld - Advancing next]\n";
static const char ADPRE[] = "[List %ld - Advancing pre]\n";
static const char INSERT[] = "[List %ld - Inserting node]\n";
static const char REMOVE[] = "[List %ld - Removing node]\n";
static const char VIEW[] = "[List %ld - Viewing node]\n";
static const char LIST_ALLOCATE[] = "[List %ld has been allocated]\n";
static const char LIST_DEALLOCATE[] = "[List %ld has been deallocated]\n";

static int debug_on = FALSE;    /* allocation of debug flag */
static long list_counter = 0;   /* the number of lists allocated so far */


/*--------------------------------------------------------------------------
Function Name:          set_debug_off
Description:            turn off the debug message
Purpose:                turn off the debug message
Input:                  void
return:                 return nothing
--------------------------------------------------------------------------*/ 
void set_debug_off (void) {
    /* debug on is false*/
    debug_on = FALSE;
}

/*--------------------------------------------------------------------------
Function Name:          set_debug_on
Description:            turn on the debug message
Purpose:                turn on the debug message
Input:                  void
return:                 return nothing
--------------------------------------------------------------------------*/

void set_debug_on (void) {
    /* debug on is true*/
    debug_on =TRUE;
}

/*--------------------------------------------------------------------------
Function Name:          advance_next_List
Description:            I first use the if statement to check is it empty
                        then check whether it NULL.
Purpose:                effectively shifts the elements of the list backwards
Input:                  
    *this_list          move this pointer to the next
return:                 return void 
--------------------------------------------------------------------------*/
void advance_next_List (List * this_list) {
    /* check whether it is empty*/
    if(isempty_List(this_list)){
        fprintf(stderr, ADNEXT_EMPTY);
    }
		/* else if ( it is equal null*/
    else if (this_list == NULL){
        fprintf(stderr, ADNEXT_NONEXIST);
    }
    else{
				/* this list access end equal this_list access end access next*/
        this_list->end = this_list->end->next;
    }
    if (debug_on){
        fprintf(stderr, ADNEXT, list_counter);
    }
}

/*--------------------------------------------------------------------------
Function Name:          advance_pre_List
Description:            I first use the if statement to check is it empty
                        then check whether it NULL.
Purpose:                effectively shifts the elements of the list forward
Input:                  
    *this_list          move the pointer to the previous
return:                 void
--------------------------------------------------------------------------*/

void advance_pre_List (List * this_list) {
    /* if it is empty*/
    if(isempty_List(this_list)){
				/* print error message*/
        fprintf(stderr, ADPRE_EMPTY);
    }
		/* check whether this_list is null*/
    else if (this_list == NULL){
        fprintf(stderr, ADPRE_NONEXIST);
    }
    else{
				/* this_list access end equal this_list
				 * access end access pre*/
        this_list->end = this_list->end->pre;
    }
    if (debug_on){
        fprintf(stderr, ADPRE, list_counter);
    }
}

/*--------------------------------------------------------------------------
Function Name:          check_to_go_forward
Description:            the alogorithm is the pointer access the occupany
                        divid by 3
Purpose:                check whether it would more efficient to reach item 
                        number, forward or backward
Input:                  
    *this_list          a pointer to the list we wish to check
		where               expect of the item in the list
return:                 return true or false 
--------------------------------------------------------------------------*/

static long check_to_go_forward (List * this_list, long where) {
    /* if the list equal null*/
    if (this_list == NULL){
        fprintf(stderr, CHECK_NONEXIST);
    }
    /* if where is less than the occupancy /2 */
    if (where <= (this_list->occupancy / TWO)){
				/* return 1*/
        return 1;
    }
		return 0;
}

/*--------------------------------------------------------------------------
Function Name:          delete_List
Description:            use if statement to check whether the list
                        equal 0, and then use the for loop to go over
												it, then free the memory
Purpose:                deallocates all memory associated with the list
Input:                  
    **lpp               double pointer to the list that we want to delete
return:                 return void
--------------------------------------------------------------------------*/

void delete_List (List ** lpp) {
    /* this is a pointer point to list*/
    List *this_list= *lpp;
		/* it is for counting the list*/
    int counter;
		/* this node is a pointer */
		Node * this_node;
		long size;
    /* size for store the occupancy*/
		size = this_list-> occupancy;

    if (debug_on){
				/* print the error message*/
        fprintf(stderr, LIST_DEALLOCATE, list_counter);
    }

    
    if (this_list == 0){
        fprintf(stderr, DELETE_NONEXIST);
    } 
		else {
				/* for loop to go over the counter */
        for(counter=0;counter<size; counter++){
				    this_node = this_list->end;
						this_list-> end = this_list-> end->next;
						/* call the delete node function */
            delete_Node(&this_node, this_list -> delete_func); 
        }
				/* free memory*/
        free(this_list);
        this_list =0;
				/* list counter decrement*/
        list_counter--;
    }
}

/*--------------------------------------------------------------------------
Function Name:          find_location
Description:            i use the if statement to check whether the list
                        is NULL first, and then i check whether it is the
												front,if it is, i call the adcance_next_list
Purpose:                find the location we want to insert or deleter
Input:                  
    *this_list          a pointer to the list we want to check
		where               expect the number of the item in the list
return:                 return a new node 
--------------------------------------------------------------------------*/

static Node * find_location (List * this_list, long where) {
    /* this variable is used for finding the location*/
    Node* newEnd;
    if (this_list->end == NULL) {
				/* return to the list access end*/
        return this_list->end;
    }
		/* if where equal 1 or where equal 0*/
		else if (where == END || where == FRONT) {
        return this_list->end;
    }
		else {
				/* it is a pointer to sotre this_list access end*/
        Node* end = this_list->end;
        long shouldGoForward = check_to_go_forward(this_list, where);
				/* it is for increment it*/
        int i = 0;
				/* this one is a condition to test efficiency*/
        if (shouldGoForward) {
            while (i++ < (where - 1)) {
                advance_next_List(this_list);
            }
        } 
				else{
				    /* step is to store the occupancy - where +1*/
            long steps = (this_list->occupancy - where + 1);
            while (steps-- > 0) {
                advance_pre_List(this_list);
            }
        }
				/* new end store this_list access end*/
        newEnd = this_list->end;
        this_list->end = end;
        return newEnd;
    }
}

/*--------------------------------------------------------------------------
Function Name:          insert
Description:            i use the if statement to check where is the 
                        location point, and insert the node to the 
												exactly location
Purpose:                insert the element into this_list 
Input:
    *this_list          its a pointer to the after we want to insert
		*element            a pointer we wish to store in new node
		*where              a pointer to the copy function passed into the list
return:                 
--------------------------------------------------------------------------*/

long insert (List * this_list, void * element, long where) {
    /* this node is to insert node*/
    Node* node;
		/* it is for finding a location to insert*/
    Node* newNode;

    /* if this list does not exist, print error statement*/    
    if (this_list == 0){
        fprintf(stderr, INSERT_NONEXIST);
        return 0;
    }
		/* if the element is equal 0*/
    if (element == 0){
        return 0;
    }
		/* this node call the find location */
    node = find_location(this_list, where);
		/* nnew node for call the insert function*/
    newNode = insert_Node(node, element, this_list->copy_func);
    
		/* if the location is not equal end or equal 0*/
    if (where == END || (this_list->occupancy == 0)) {
        this_list->end = newNode;
    }
    /* increment the occupancy*/
    this_list->occupancy++;
    
    if (debug_on){
        fprintf (stderr, INSERT, list_counter);
    }
    return 1;
}

/*--------------------------------------------------------------------------
 Function Name:          isempty_List
 Description:            we test whether the list exist, if it equal null
                         , if yes, return ture, else return false
  Purpose:               check whether the list is empty
 Input:
 *this_list              it is a pointer we want to check whether is it empty
 return:                 return true or false
 --------------------------------------------------------------------------*/

long isempty_List (List * this_list) {
    /* if the list exist*/
    if(this_list){
        /* if this list point to end equal null*/
        if (this_list->end == NULL){
            /*return true*/
            return 1;
        }
				else {
            return 0;
        }
    }
		else {
        /* print the error statement*/
        fprintf(stderr, ISEMPTY_NONEXIST);
    }
    return 0;
}

/*--------------------------------------------------------------------------
 Function Name:          new_List
 Description:            This function asks for input and displays output
 Purpose:                allocate and initializes memory
 Input:                  
     copy_func           a pointer to the function that can copy elements
		 delete_func         a pointer to the function which free memory
		 write_func          a pointer to the function which writes elements
 return:                 this_List
 --------------------------------------------------------------------------*/

List * new_List (
                 void *(*copy_func) (void *),
                 void (*delete_func) (void *),
                 FILE *(*write_func) (void *, FILE *)) {
    
    /*allocate*/
    List * this_List = (List*) malloc (sizeof(List));
    
    /*initialize*/
    this_List -> end = NULL;
    this_List -> list_count=1;
    this_List -> occupancy =0;
    this_List -> copy_func=copy_func;
    this_List -> delete_func = delete_func;
    this_List -> write_func = write_func;
		/* if debug on*/
    if (debug_on){
				/* print the error message*/
        fprintf(stderr, LIST_ALLOCATE, list_counter);
    }
    return this_List;
}

/*--------------------------------------------------------------------------
Function Name:          remove_List
Description:            we need to use find location to check where
                        we want to delete, so I set four situations
												we need to check the where is end or 
												where equal this list access occupancy
												and then everytime I run the prgram, i need to
												decrement it.
Purpose:                remove an element in this_list at location where
Input:                  
    this_list           pointer to the list we want to remove
		where               expected the place in the number of the element
return:                 return list_count
--------------------------------------------------------------------------*/

void * remove_List (List * this_list, long where) {
    /* a node pointer use for checking location */
    Node* node;
		/* removedNOde store the deleted node*/
		Node* removedNode;
    if (debug_on){
        fprintf (stderr, REMOVE, list_counter);
    }
    /* if this_list access occupancy*/
    if (this_list->occupancy == 0) {
				/* print the error message*/
        fprintf(stderr, REMOVE_EMPTY);
				/* return 0*/
        return NULL;
    }
    
    node = find_location(this_list, where);
		/* if where equal front*/
    if (where == FRONT) {
        /* if node equal node access next*/
        node = node->next;
    } 
		else if (where == END) {
				/* this list access end equal node pre*/
        this_list->end = node->pre;
    } 
		else {
        node = node->next;
    }
		/* removenode call the remove node function*/
    removedNode = remove_Node(node);
		/* occupancy decretment*/
    this_list->occupancy--;

    if (this_list->occupancy == 0) {
        this_list->end = NULL;
    }
		/* return the removedNode to the function */
    return removedNode;
}


/*--------------------------------------------------------------------------
Function Name:          view
Description:            use if statement to check whether is it null
                        and empty. if where is not equal 1, the temp
												node will access next
Purpose:                store at location where for viewing
Input:                  
    *this_list          pointer to the list we wish to check
		where               expecter the place in the list we want to hold and 
		                    see
return:                 return view_Node function
--------------------------------------------------------------------------*/

void * view (List * this_list, long where) {
    /* temp node for calling the find location */
    Node* temp = find_location(this_list,where);
    
    if (this_list == NULL){
        fprintf(stderr, VIEW_NONEXIST);
    }
    else if (isempty_List(this_list)){
        fprintf(stderr, VIEW_NONEXISTNODE);
    }
    if (debug_on){
        fprintf(stderr, VIEW, list_counter);
    }
    /* if where is not equal 0 */
    if (where != END) {
				/* temp node access next*/
        temp = temp->next;
    }
    return view_Node(temp);
}



FILE * write_List (List * this_list, FILE * stream) {
    long count;             /* to know how many elements to print */
    Node * working;         /* working node */
    
    if (!stream) {
        fprintf (stderr, WRITE_NONEXISTFILE);
        return NULL;
    }
    
    if (!this_list) {
        fprintf (stderr, WRITE_NONEXISTLIST);
        return NULL;
    }
    
    if (stream == stderr)
        fprintf (stream, "List %ld has %ld items in it.\n",
                 this_list->list_count, this_list->occupancy);
    
    if (!this_list->write_func) {
        fprintf (stream, WRITE_MISSINGFUNC);
				    return stream;
    }
    
    if (this_list->occupancy >= 1)
        working = this_list->end->next;
    
    for (count = 1; count <= this_list->occupancy; count++) {
        if (stream == stderr)
            fprintf (stream, "\nelement %ld:  ", count);
        write_Node (working, stream, this_list->write_func);
        working = working->next;
    }
    
        
    return stream;
}

/*--------------------------------------------------------------------------
Function Name:          write_reserve_List
Description:            using four if statemen to check wheather 
                        it is on the stream, and whether it is on 
												the list, and we need to use th for loop to 
												reserve th list.
Purpose:                reverse the list and print it to filestream
Input:             
    *this_list          expect the value we wish to write
		*stream             expext to be either stdout ot stderr
return:                 return stream
--------------------------------------------------------------------------*/


FILE * write_reverse_List (List * this_list, FILE * stream) {
    /* how many elements to print*/
    long count; 
    /* working node*/
    Node * working;
    /* if it is not in the stream*/
    if (!stream) {
        fprintf (stderr, WRITE_NONEXISTFILE);
				return NULL;
    }
    /* if this list is not exist*/
    if (!this_list) {
        fprintf (stderr, WRITE_NONEXISTLIST);
				return NULL;
    }
    /* if the stream equal error message*/
    if (stream == stderr)
        fprintf (stream, "List %ld has %ld items in it.\n",
				this_list->list_count, this_list->occupancy);
    /* if this_list access write_function is false*/
    if (!this_list->write_func) {
				fprintf (stream, WRITE_MISSINGFUNC);
				return stream;
    }
    /* if this_list access occupance greather than 1*/
    if (this_list->occupancy >= 1)
        working = this_list->end;
    /* a for loop to go over the occupancy*/
    for (count = 1; count <= this_list->occupancy; count++) {
        if (stream == stderr)
				fprintf (stream, "\nelement %ld:  ", count);
				write_Node (working, stream, this_list->write_func);
				/* it is the important step to reserve */
				working = working->pre;
    }

    return stream;
}
static void delete_Node (Node ** npp, void (*delete_func) (void *)) {
    
    /* does the node exist??? */
    if (!npp || !*npp) {
        fprintf (stderr, DELETE_NONEXISTNODE);
        return;
    }
    
    /* call function to delete element */
    if (delete_func && (*npp)->data)
        (*delete_func) (&((*npp)->data));
        /* delete element */
				free (*npp);
        /* assign node to NULL */
				*npp = NULL;
}

/*--------------------------------------------------------------------------
Function Name:          insert_Node
Description:            use the if statement to check whether it is null
                        if it is, the working will access pre, and the 
								        working will access next, and then return working
												to the function
Purpose:                create a new node to hold element
Input:                  
 *this_Node             a pointer to the node after we wish to insert 
                        a new node
 *element               pointer to object we wish to stroe in the new node
 *copy function         pointer to copy function pass into the list or null
return:                 return Node
--------------------------------------------------------------------------*/

static Node * insert_Node (Node * this_Node, void * element,
                           void * (*copy_func) (void *)) {
    /* working node call the new node function*/
    Node * working = new_Node(element, copy_func);
		/* if the pointer equal null*/
    if (this_Node == NULL) {
				working->pre= working;
				/* working access next equal working*/
        working->next = working;
    } 
		else {
        Node* next = this_Node->next;
        /* working access pre equal this_Node*/
        working->pre = this_Node;
        /* working access pre equal this_Node*/
        working->next = this_Node->next;
        
        this_Node->next = working;
        next->pre = working;
        
    }
    return working;
}



static Node* new_Node (void * element, void * (*copy_func) (void *)) {
    
    /* allocate memory */
    Node *this_Node = (Node *) malloc (sizeof (Node));
    
    /* initialize memory */
    this_Node->next = this_Node->pre = NULL;
    this_Node->data = (copy_func) ? (*copy_func) (element) : element;
    return this_Node;
}

/*--------------------------------------------------------------------------
Function Name:          remove_Node
Description:            using the if statement to know the exatly location
                        in the list, and then removing it
Purpose:                return a pointer to this_node's data
Input:                  
    this_node           its a pointer we wish to show
return:                 return data 
--------------------------------------------------------------------------*/

static void * remove_Node (Node * this_Node) {
    /* a data store this_node access data*/
    void * data = this_Node->data;
		/* this_Node access previous accees next*/
    this_Node-> pre->next = this_Node->next;
    this_Node-> next->pre = this_Node->pre;
		/* call the delete_node function*/
    delete_Node(&this_Node,NULL);

    return data;
}

/*--------------------------------------------------------------------------
 Function Name:          view_Node
 Description:            I first check whether the node existing,
                         if not, return this_node access data
 Purpose:                Node data we want to see
 Input:                  
 *this_Node              a pointer to the node we want to see
 return:                 this_Node->data 
 --------------------------------------------------------------------------*/

static void * view_Node (Node * this_Node) {
    /* if this_node doesnt exist */
    if (!this_Node){
				/* call the error message*/
        fprintf(stderr, VIEW_NONEXISTNODE);
        return NULL;
    }
    else{
				/* return this_Node access data to the function*/
        return this_Node->data;
    }
}

static FILE* write_Node (Node * this_Node, FILE * stream,
                         FILE * (*write_func) (void *, FILE *)) {
    
    if (!stream) {
        fprintf (stderr, WRITE_NONEXISTFILE);
        return NULL;
    }
    
    if (!this_Node) {
        fprintf (stream, WRITE_NONEXISTNODE);
        return stream;
    }
    
    if (!write_func) {
        fprintf (stream, WRITE_MISSINGFUNC);
        return stream;
    }
    return (*write_func) (this_Node->data, stream);
}
