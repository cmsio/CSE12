/**
 * Name: ChakMan Sio, Mengyu Yang
 * Class: CSE 12 
 * Account cs12xef; cs12xfh
 * Quarter: Fall 2016 
 * Assignment: HW9
 *
 * File name: Tree.c
 * Description: This filre contains two constructs. Together, this file will 
 *			implement a binary tree and enable some operations about this tree.
 *
 * Struct name: TNode<Whatever> 
 * Description: this struct contains TNode constructor, read method and 
 *			constructor, write method and constructor,TNode remove, RARM, and
 *			SetHeightAndBalance. This struct implement TNode part of the 
 *			binary tree.
 * Class name: Tree<Whatever>
 * Description: this struct implements Tree constructor and desconstructor, 
 *			Tree insert, lookup, and remove, and incrementCost, incrementOperation,
 *			getOperation, getCost and ResetRoot. This struct is able to do operation
 *			about TNodes to the tree and to get efficiency information. 
 *
 */

#include <stdlib.h>
#include <string.h>
#include "Tree.h"

// debug messages
static const char ALLOCATE[] = " - Allocating]\n";
static const char COST_READ[] = "[Cost Increment (Disk Access): Reading ";
static const char COST_WRITE[] = "[Cost Increment (Disk Access): Writing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char TREE[] = "[Tree ";

template <class Whatever>
int Tree<Whatever>::debug_on = 0;

template <class Whatever>
long Tree<Whatever>::cost = 0;

template <class Whatever>
long Tree<Whatever>::operation = 0;

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
struct  TNode {
// friends:

// data fields:
	Whatever data;
	long height;
	long balance;
	offset left;
	offset right;
	offset this_position;	// current position

  // function fields:
	TNode () : height (0), balance (0), left (0), right (0), 
		this_position (0) {}

	// to declare the working TNode in Tree's Remove
	TNode (Whatever & element) : data (element), height (0), balance (0),
		left (0), right (0), this_position (0) {}
	
	TNode (Whatever &, fstream *, long &);	// to add new node to disk
	TNode (const offset &, fstream *);	// to read node from disk
	
	unsigned long Insert (Whatever &, fstream *, long &, offset &);
	// optional recursive Lookup declaration would go here
	void Read (const offset &, fstream *);	// read node from disk
	unsigned long Remove (TNode<Whatever> &, fstream *, long &, offset &,
		long fromSHB = FALSE);
	void ReplaceAndRemoveMin (TNode<Whatever> &, fstream *, offset &);
	void SetHeightAndBalance (fstream *, offset &);
	void Write (fstream *) const;		// update node to disk

	ostream & Write_AllTNodes (ostream &, fstream *) const;
};

/**
 *Method: Tree<Whatever> :: Insert
 *Description: The method inserts TNodes in the tree by calling the TNode
 *			insert method recursively.
 *Inout: Whatever & element			the element to be inserted in the tree
 *Output: long	return 1 if the insertion is successful; return 0 otherwise
 */

template <class Whatever>
unsigned long Tree<Whatever> :: Insert (Whatever & element) {
 IncrementOperation();

	/*construct a tnode*/
  if(occupancy == 0){
    //call write constructror, since it's the first node
    TNode<Whatever> newNode (element, fio, occupancy);
		return 1;
  }
  else{
    /*read the root tnode*/
    TNode<Whatever> rootTNode (root, fio);
    /*call tnode recursively on root tnode*/
		return (rootTNode.Insert(element, fio, occupancy, root));
  }
  /*increment the operation value*/
   //return 0;
}

/*
 *Name: TNode<Whatever> ;: ReplaceAndRemoveMin
 *Description: Called when removing a TNode with 2 children, replaces that 
				TNode with the minimum TNode in its right subtree to maintain the
				Tree structure. 
 *Input: TNode<Whatever> :: targetTNode:  be a reference to the TNode to 
				remove that has 2 children
 *			fstream * fio:  file stream corresponding to the datafile where the
 *			Tree is stored on disk.	
 *			offset & PositionInParent: a reference to the TNode position in the
 *			parent TNode used to get to the current TNode's offset in the datafile.
 *OutPut: none
 */

template <class Whatever>
void TNode<Whatever> :: ReplaceAndRemoveMin (TNode<Whatever> & targetTNode, 
	fstream * fio, offset & PositionInParent) {
		
  /*if it is left*/
  if(left){
    /*read the left tnode*/
    TNode<Whatever> LeftTNode(left,fio);
    /* left call the replaceandremovemin function*/
    LeftTNode.ReplaceAndRemoveMin(targetTNode,fio, left);
    SetHeightAndBalance(fio,PositionInParent);
  }
  else{
    /*targetTNodedata euqal data*/
    targetTNode.data= data;
    /*update position in parent*/
    PositionInParent = right;
  }
}

/*
 *TNode<Whatever> :: Remove
 *Description: this method removes given element from the tree by calling 
 *			itself recursively.
 *Input: TNode<Whatever> & elementTNode:  a reference to the TNode containing
				the data that identifies the element to remove.
 *			fstream * fio:  filestream corresponding to the datafile where the Tree 
 *			is stored on disk.
 *			long & occupancy:  the occupancy of the tree
 *			offset & PositionInParent:   the TNode position in the parent TNode 
 *			used to get to the current TNode's offset in the datafile.
 *			long fromSHB:  to be true or false, keeping track of whether or not 
 *			Remove was called from SetHeightAndBalance so that Remove can determine
 *			whether or not to call SetHeightAndBalance.
 *Output: return 1 if remove is successful; return 0 otherwise
 */
template <class Whatever>
unsigned long TNode<Whatever> :: Remove (TNode<Whatever> & elementTNode,
	fstream * fio, long & occupancy, offset & PositionInParent,long fromSHB) 
{
  /*the element to keep track of the return value of remove*/ 
  long keep_tracking = 0;
	/*if there is a match*/
  if (elementTNode.data == (data)){
    /*update the date*/
    elementTNode.data = data;
    /*decrement the occupancy*/
    occupancy--;
    /*there there are two children*/
    if (left && right ){
      /*right call the RARM*/
      TNode<Whatever> RightTNode(right,fio);
      RightTNode.ReplaceAndRemoveMin(*this, fio, right);
      if(!fromSHB){
        SetHeightAndBalance(fio,PositionInParent);
      }
      else{
        Write(fio);
      }
    }

    /*if it's a leaf*/
    else if (!(left) && !(right)){
      /*update positioninparent to null*/
      PositionInParent = NULL;  
    }
    /*if only have left*/								
    else if (left){
      // pointerInparent equal left
      PositionInParent= left ; 
    }
    /*if only have right child*/
    else if (right){
      /*PointerInParenet equal right*/
      PositionInParent = right;
    }
    else {
      PositionInParent = this_position;
    }
    /*return true*/
    return 1;
  }
           
  else{
    // if elementTNode is less thatn data, go left
    if(elementTNode.data < (data)){
      //if left is not null
      if(left){
        //read constructor
        TNode<Whatever> LeftTNode(left,fio);
				// remove left
        keep_tracking=LeftTNode.Remove(elementTNode, fio,occupancy, left, 0);
      }
      else{
        return 0;
      }
    }
    else{
      // if it is right
      if (right){
        TNode<Whatever> RightTNode(right,fio);
				// remove right
				keep_tracking = RightTNode.Remove(elementTNode, 
        fio, occupancy, right, 0);
      }
      else{
        return 0;
      }
    }
  }

	if (!fromSHB){
    // call setheightandbalance
    SetHeightAndBalance(fio,PositionInParent);
  }

  return keep_tracking ;
}


/*Name: Tree<Whatever> :: Remove(Whatever & element)
 *Description: Removes an element from the Tree by calling TNode's remove 
 *			method recursively
 *Input: Whatever & element			the element to be deleted
 *Output: return 1 if it's successful; return 0 otherwise
 */
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {
  IncrementOperation();
  //this variable is for store the data from root call remove function
  int store_data;
    		
  //if root is empty
  if (occupancy == 0){
    return 0;
  }
  // create a new TNode to store the data
  TNode<Whatever> read_data(root, fio);
  TNode<Whatever> elementTNode(element);
  // it use for store data
  store_data = read_data.Remove(elementTNode, fio, occupancy,root, 0);
  element = elementTNode.data;
  /*if the tree is empty, reset root*/
  if (occupancy == 0){
    ResetRoot();
  }

  //IncrementOperation();
  return store_data;
}

/*
 *Method: TNode<Whatever> :: SetHeightAndBalance
 *Description: this method sets height and balance for current TNode. And check
 *			if current Tree exceeds the threshold case. if so, readjust the tree.
 *Input: fstream * fio	the filestream corresponding to the datafile 
 *				where the Tree is stored on disk.
 *			offset & PositionInParent				a reference to the TNode position in 
 *			the parent TNode used to get to the current TNode's offset 
 *			in the datafile.
 *Output: none
 */
template <class Whatever>
void TNode<Whatever> :: SetHeightAndBalance (fstream * fio,
	offset & PositionInParent) {
  // this variable is order to get the left's height
  long right_height =-1;
  // this variable is order to get the left's height
  long left_height = -1;
	//variable to store the occupancy
  long occupancy = -1;

  // if left exist
  if (left){
    //read left and get its height
    TNode<Whatever> readLeftTNode(left,fio);
    left_height = readLeftTNode.height;
  }

  // if right exist
  if (right){
    /*read right and get its height*/
    TNode<Whatever> readRightTNode(right,fio);
    right_height = readRightTNode.height;
  }
  //height = max(left, right) +1
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
   // TNode<Whatever> elementTNode(this_position, fio);// test;
	  TNode<Whatever> elementTNode(data);
    Remove(elementTNode, fio, occupancy, PositionInParent,1);
    // cal the remove function 
    TNode<Whatever> parentTNode(PositionInParent, fio);
		//re-insert the tnode into the tree
    parentTNode.Insert(elementTNode.data,fio, occupancy,PositionInParent);
    return;
  }
	//write to the disk
  Write(fio);
}

/*
 *Name: Tree<Whatever> :: GetCost()
 *Description: get the value of the cost variable
 *Input: none
 *Output: cost:	the value of Tree<Whatever> :: cost variable
 */
template <class Whatever>
long Tree <Whatever> :: GetCost () {
  /*return the value of cost variable*/
	return cost;
}

/*
 *Name: Tree<Whatever> :: GetOperation
 *Description: get the value of the operation variable
 *Input: none
 *Output: operation:		the value of Tree<Whatever> :: operation variable
 */
template <class Whatever>
long Tree <Whatever> :: GetOperation (){
  /*return the value of operation*/
  return operation;
}

/*
 *Name: Tree<Whatever> :: IncrementCost()
 *Description: increment the value of cost variable when the function is 
 *			is called, that is when a read or write to disk occurs.
 *Input: nonea
 *Output: none
 */
template <class Whatever>
void Tree <Whatever> :: IncrementCost () {
  /*increment the value of cost variable*/
	cost++;
}

/*
 *Name: Tree<Whatever> :: IncrementOperation()
 *Description: increment the value of operation variable when the function 
 *			is called, that is when a Tree operation occurs.
 *Input: none
 *Output: none
 */
template <class Whatever>
void Tree <Whatever> :: IncrementOperation () {
  /*incremtn the value of cost variable*/
	operation++;
}


/*
 *Name: Tree<Whatever> :: ResetRoot()
 *Description: Resets the root datafield of this tree to be at the end of the 
 *			datafile. This should be called when the last TNode has been 
 *				removed from the Tree. 
 *Input: none
 *Output: none
 */
template <class Whatever>
void Tree <Whatever> :: ResetRoot () {
  /*find the end*/
  fio->seekg(0, ios :: end);
  /*reset root to the end */
  root = fio->tellg();
}

/*
 *Name: TNode<Whatever> :: Insert
 *Description: The TNode's insert method to insert tnodes into a binary tree
 *			by recursive call
 *Input: Whatever & element			the data to be stored in the TNode
 *			fstream * fio		the filestream corresponding to the datafile 
 *			where the Tree is stored on disk
 *			long & occupancy				a reference to the occupancy of the tree
 *			offset & PositionInParent				a reference to the TNode position in the
 *			parent TNode used to get to the current TNode's offset in the datafile.
 *Output: return 1 if insertion is successful; return 0 otherwise
 */
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (Whatever & element, fstream * fio,
	long & occupancy, offset & PositionInParent) {
  /*if there is a match*/
	if (element == data){
    /*store element in data*/
    data = element;
		/*write on the disk*/
		Write(fio);
		return TRUE;
	}
  /*go left*/
	else if (element < data){
    /*if left does not exist*/
    if(!left){
      /*write the tnode*/
			TNode<Whatever> leftTNode(element, fio, occupancy);
      /*update the value of left*/
			left = leftTNode.this_position;
		}
		/*left exists*/
		else {
				/*read the left*/
				TNode<Whatever> readLeftTNode(left, fio);
				/*recursive call*/
				readLeftTNode.Insert(element, fio, occupancy, left);
				
		}
  }
	/*go right*/
	else {
    /*if right does not exist*/
		if(!right){
				 /*write the tnode*/
		     TNode<Whatever>readRightTNode(element, fio, occupancy);
				 /*update the value of right*/
				 right = readRightTNode.this_position;
		}
		/*if right exist*/
		else{
				TNode<Whatever> readRightTNode(right, fio);
				/*recursive call*/
				readRightTNode.Insert(element, fio, occupancy, right);
				
		}
	}
	/*set height and balance for this tnode*/
	SetHeightAndBalance(fio, PositionInParent);
	return 1;
}

/*
 *Name: Tree<Whatever> :: Lookup
 *Description: check if an element is in the tree by useing a while loop
 *			to loop through the tree
 *Input: Wharever & element:		the data stored in the tnode that to be checked
 *Output: return 1 if the element is in the tree; return 0 otherwise
 */

template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {
  IncrementOperation();
  /*variable to store current position in the tree, start from the root*/
  offset this_position = root;
	/*while still in the tree*/
  while(this_position != 0){
    /*read current tnode*/
    TNode<Whatever> READ_NODE (this_position, fio);
		  /*of there is a match*/
      if(element == READ_NODE.data){
				/*update the date*/
        element = READ_NODE.data;
				
			  return true;
      }
      else if (element < READ_NODE.data){
        /*update this_postion to left*/
				this_position = READ_NODE.left;
      }
			else {
				/*update this_position to right*/
        this_position = READ_NODE.right;
      }
  }
  return 0;
}


/*
 *Name: TNode<Whatever> :: Read
 *Description: Reads a TNode which is present on the datafile into memory. 
				The TNode is read from position. The TNode's information in the 
				datafile overwrites this TNode's data.  
 *Input: const offset & position:				offset in the datafile corresponding to 
				the position of the TNode we wish to read into memory.
 *			fstream * fio:	 the filestream corresponding to the datafile where 
 *			the Tree is stored on disk
 *Output: void
 */
template <class Whatever>
void TNode<Whatever> :: Read (const offset & position, fstream * fio) {
  /*find the current position*/
	fio->seekg(position);
	/*read*/
  fio-> read((char *) this, sizeof(TNode<Whatever>));
  /*increment cost*/
	Tree<Whatever>:: IncrementCost();
}

/*
 *Name: TNode<WHatever> :: TNode
 *Description: the TNode read constructor. Called when reading a TNode present
 *			on disk into memory.
 *Input: const offset & position:				the offset in the datafile 
				corresponding to the position of the TNode we wish to read into memory
 *			fstream * fio:	the filestream corresponding to the datafile where 
 *			the Tree is stored on disk.
 *Output: none
 */
template <class Whatever>
TNode<Whatever> :: TNode (const offset & position, fstream * fio) {
    /*call read method*/
    Read(position, fio);
		/*debug message*/
  	if (Tree<Whatever>:: debug_on){
      cerr<< COST_READ<<(const char*)this<<"]\n";
    }

}

/*
 *Name: TNode<Whatever> :: TNode
 *Description: the TNode write constructor, called when creating TNode for 
 *			creating a TNode for the first time
 *Data Field:
 *			data(element)		-holds the element stored in the tnode
 *			height(0)				-initialize the height of the tnode to 0
 *			balance(0)			-initialize the balance of the tnode to 0
 *			left(0)					- initialize the offset left to 0
 *			right(0)				-initialize the offset right to 0
 *Inputr: Whatever & element:		 be the data to be stored in the TNode. 
				They must be of the same type as the rest of the objects present 
				in the Tree.
				ftream * fio:		be the filestream corresponding to the 
				datafile where the Tree is stored on disk
				long & occupancy:				a reference to the occupancy of the tree to 
				wich the new Node is being added.
 *Output: none
 */
template <class Whatever>
TNode<Whatever> :: TNode (Whatever & element, fstream * fio, long & occupancy): 
			data (element), height (0), balance (0), left (0), 
			right (0) {
	// seek to ending of file			
  fio->seekp (0, ios :: end);
	/*update this_position */
  this_position = fio -> tellp();
	occupancy++;
	/*write on disk*/
	Write (fio);
}

/*
 *Name: TNode<Whatever> :: Write
 *Descruption:	TNode's Write method. Writes this TNode object to disk at 
				this_position in the datafile. 
 *Input: 
     fstream * fio:    the filestream corresponding to the
 *			datafile where the Tree is stored on disk.		
 *Output: none
 */
template <class Whatever>
void TNode<Whatever> :: Write (fstream * fio) const {
    /*increment cost*/
    Tree<Whatever>:: IncrementCost();
    /*find this_posotion*/
		fio-> seekp(this_position);
		/*write it on the disk*/
    fio->write((const char*) this, sizeof (TNode<Whatever>));
		/*debug message*/
		if (Tree<Whatever>:: debug_on){
      cerr<< COST_WRITE<<(const char*)this<<"]\n";
    }
}


/*
 *Name: Tree<Whatever> :: Tree
 *Description: the tree constructor.Allocates the tree object. 
 *				     Checks the datafile to see if it contains Tree data. 
 *				     If it is empty, root and occupancy fields are written 
 *				     to the file. If there is data in the datafile, root 
 *				     and occupancy fields are read into memory.  
 *datafield:		
     fio			 create mew fstrea, to store datafilr, inputstrem
 *			       and outputstream
 *Input:       const char * datafile:	be the filestream corresponding 
               to the datafile where the Tree is to be stored on disk.	
 *Output:      none
 */
template <class Whatever>
Tree<Whatever> :: Tree (const char * datafile) :
	fio (new fstream (datafile, ios :: out | ios :: in)) {
	/*check for empty file*/
	fio -> seekp(0, ios::beg);
	/*update the beginning*/
	offset beginning = fio -> tellp();
	/*seek the end*/
	fio -> seekp(0, ios::end);
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
	/*store the ending*/
	offset ending = fio -> tellp();
  /*set count back to 0*/
	tree_count = 0;	
	/*set root back to null*/
	root = 0;
	/*set occupancy to 0*/
	occupancy = 0;
	/*file is empty*/
	if(beginning == ending){
		/*reserve space*/
		fio -> seekp(0, ios::beg);
		/*write*/
		fio -> write((const char *) &root, sizeof(root));
		fio -> write((const char *) &occupancy, sizeof(occupancy));
		/*reset root*/
		root = fio -> tellp();
		
	}
	/*not empty*/
	else{
		/*read root and occupancy from the disk*/
		fio -> seekg(0,ios:: beg);
		fio -> read((char *) &root, sizeof(root));
		fio -> read((char *) &occupancy, sizeof(occupancy));
		
	}
	/*increment count*/
	tree_count++;
  /*debug messsage*/
	if(debug_on == TRUE){
      cerr<< TREE<< tree_count<< ALLOCATE;
  }

}

/*
 *Name: Tree<Whatever> :: Set_Debug_On()
 *Description: set debug flag to true
 *Input: none
 *Output: none
 */
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On(){
	/*set debug flag to true*/
	debug_on = 1;
}

/*
 *Name: Tree<WHatever> :: Set_Debug_Off()
 *Description: set debug flag false
 *Input: none
 *Output: none
 */
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off(){
	/*set debug flag to false*/
	debug_on = 0;
}


template <class Whatever>
Tree<Whatever> :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
	/*debug message*/			
  if (debug_on == TRUE){
      cerr<< TREE<<tree_count<< DEALLOCATE;
  }
	/*seek for beginning*/
  fio ->seekp(0,ios ::beg);
  /*write*/
	fio->write((const char *) &root, sizeof (root));
	fio->write ((const char *) &occupancy, sizeof (occupancy));
  /*delete stream*/
	delete fio;
	/*decrement occupancy*/
	occupancy--;
}	/* end: ~Tree */


template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
	stream << "at height:  :" << nnn.height << " with balance:  "
		<< nnn.balance << "  ";
	return stream << nnn.data << "\n";
}

template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This funtion will output the contents of the Tree table
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
  long old_cost = cost;

	stream << "Tree " << tree_count << ":\n"
		<< "occupancy is " << occupancy << " elements.\n";

	fio->seekg (0, ios :: end);
	offset end = fio->tellg ();

	// check for new file
	if (root != end) {
		TNode<Whatever> readRootNode (root, fio);
		readRootNode.Write_AllTNodes (stream, fio);
	}

        // ignore cost when displaying nodes to users
        cost = old_cost;

	return stream;
}

template <class Whatever>
ostream & TNode<Whatever> ::
Write_AllTNodes (ostream & stream, fstream * fio) const {
	if (left) {
		TNode<Whatever> readLeftNode (left, fio);
		readLeftNode.Write_AllTNodes (stream, fio);
	}
	stream << *this;
	if (right) {
		TNode<Whatever> readRightNode (right, fio);
		readRightNode.Write_AllTNodes (stream, fio);
	}

	return stream;
}

