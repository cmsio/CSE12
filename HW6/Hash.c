/**
 * Name: ChakMan SIo
 * Class: CSE 12
 * Account cs12xef
 * Quarter: Fall 2016
 * Assignment: HW6 
 * File name: Hash.c
 * Description: We are leaning Hash table in this assignment, and
 *              it can allow variable assignment to the calculator
 *              we use bully algorithm to make probing
 */

#include <cstdlib>
#include <string.h>
#include "Hash.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

using namespace std;

/* debug messages */
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_INSERT[] = " - Insert]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char FULL[] = " is full...aborting...]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT_BUMP[] = "[bumping to next location...]\n";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";


long HashTable :: debug = 0;
int HashTable :: counter = 0;


void HashTable :: Set_Debug (long option)

/***************************************************************************
 % Routine Name : HashTable :: Set_Debug (public)
 % File :         Hash.c
 %
 % Description :  This function sets debug mode on or off
 %
 % Parameters descriptions :
 %
 % name               description
 % ------------------ ------------------------------------------------------
 % option             true should set debug mode on, false should set debug
 %                    mode off.
 ***************************************************************************/

{
    // it is used for turn on or turn off debug message
    debug = option;
}


HashTable :: HashTable (long sz) : size (sz),
table_count(++counter), occupancy (0), table (new Base *[sz])
/***************************************************************************
 % Routine Name : HashTable :: HashTable (public)
 % File :         Hash.c
 %
 % Description :  This function allocates an initializes the memory
 %                associated with a hash table.
 %
 % Parameters descriptions :
 %
 % name               description
 % ------------------ ------------------------------------------------------
 % size               The number of elements for the table...MUST BE PRIME!!!
 ***************************************************************************/

{
    int index =0;
		// loop around the index
    for (index=0; index<size;index++){
				// table [inedx] = null
        table[index] = NULL;
    }
    if (debug){
        cerr<< HASH<<table_count<< DEBUG_ALLOCATE;
    }
}	/* end: HashTable */

HashTable :: ~HashTable (void)
/***************************************************************************
 % Routine Name : HashTable :: ~HashTable  (public)
 % File :         Hash.c
 %
 % Description :  deallocates memory associated with the Hash Table.  It
 %                will also delete all the memory of the elements within
 %                the table.
 ***************************************************************************/

{
    int index;
    for (index=0; index<size;index++){
				// if table[index] !=NULL
				if(table[index] !=NULL){
            delete table[index];
				}
    }
		// delete table
    delete[] table;
		table = NULL;
}	/* end: ~HashTable */


long HashTable :: Insert (Base * element, long recursiveCall)
/***************************************************************************
 % Routine Name : HashTable :: Insert (public)
 % File :         Hash.c
 %
 % Description : This function will insert the element in the hash table.
 %	             If the element cannot be inserted, false will be returned.
                 If the element can be inserted, the element is inserted and
                 true is returned. Duplicate insertions will cause the existing
                 element to be deleted, and the duplicate element to take its
                 place.
 %
 % Parameters descriptions :
 %
 % name               description
 % ------------------ ------------------------------------------------------
 % element            The element to insert.
 % recursiveCall      Whether the call to this function is recursive or not.
 % <return>           1 or 0 indicating success or failure of insertion
 ***************************************************************************/

{
    if (recursiveCall == 0) {
        index = (long)* element %size;
    }
    
    if (debug){
        cerr<<HASH<<table_count<<DEBUG_INSERT;
    }
    
    // this variable is used to store the location
    const Base *temportory_location = Locate (element);
    Base *temportory_base;
    
		// if the occupany = size, it will full
    if (occupancy == size){
        if (debug){
            cerr<<FULL<<"\n";
            
        }
				return 0;
    }

    // if temportory location is null
    if(temportory_location == NULL){
				// if thable[index] is null
        if (table[index] == NULL){
				    // table[index] = element
            table[index] = element;
            occupancy++;
            return 1;
        }
        else{
				    // set the recursivecall is true 
            recursiveCall = true;
						// use the temportory 
            temportory_base = table [index];
            table[index] = element;
            
						// this variable is for increment
            int increment = ((long)* element %(size -1))+1;
            index = (index +increment)% size;
            
            if (debug){
                cerr<< HASH<<table_count<< INSERT_BUMP;
            }
						// call the insert function
            return Insert (temportory_base, recursiveCall);
        }
    }
    // if temportory_location is not equal null
    else if(temportory_location != NULL){
				delete table[index];
				// table[index] = element
        table[index] = element;
				return 1;
    }
    else{
				// return false
        return 0;
    }
    return 1;
}


const Base * HashTable :: Locate (Base * element) const
/***************************************************************************
 % Routine Name : HashTable :: Locate (private)
 % File :         Hash.c
 %
 % Description : This function will locate the location in the
                 table for the insert or lookup.
 %
 % Parameters descriptions :
 %
 % name               description
 % ------------------ ------------------------------------------------------
 % element            The element needing a location
 % <return>           item found, or null if not found
 
 ***************************************************************************/

{
    // calculate the increment
    int increment = ((long)* element %(size -1))+1;
    
    if(debug){
        cerr<<HASH<<table_count<<DEBUG_LOCATE;
        cerr<<PROCESSING<< (char*) * element<<"]"<<"\n";
        cerr<<HASH_VAL<<(long)* element <<"]"<<"\n";
    }
    // it is use to calculate the array size
    int counter = 0;
    
    while (counter < size){
        if (debug){
            cerr<<TRYING<<index<<"]"<<"\n";
        }
				// if the table[index is null]
        if (table[index] == NULL){
            return NULL;
        }
        // if table [index is less than element]
        if(*table[index] < *element){
            return NULL;
        }
        // if table[index] equal element
        if (*table[index] == *element){
            return element;
        }
				// calculate the index
        index = (index +increment)% size;
        // increment it 
        counter++;
    }
    
    return NULL;
}


const Base * HashTable :: Lookup (Base * element) const
/***************************************************************************
 % Routine Name : HashTable :: Lookup (public)
 % File :         Hash.c
 %
 % Description : This function will lookup the element in the hash table.  If
 %               found a pointer to the element is returned.  If the element
 %               is not found, NULL will be returned to the user.
 %
 % Parameters descriptions :
 %
 % name               description
 % ------------------ ------------------------------------------------------
 % element            The element to insert or to lookup.
 % <return>           A pointer to the element if found, else NULL
 ***************************************************************************/

{
    if (debug){
        cerr<<HASH<<table_count<<DEBUG_LOOKUP;
    }
    // recalculate the index
    index = (long)* element %size;
		// if location is not equal 0
    if (Locate(element) != 0){
				// return the table[index]
        return table[index];
    }
    else{
        return 0;
    }
}


ostream & HashTable :: Write (ostream & stream) const
/***************************************************************************
 % Routine Name : HashTable :: Write (public)
 % File :         hash.c
 %
 % Description : This funtion will output the contents of the hash table
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
    stream << "Hash Table " << table_count << ":\n"
    << "size is " << size << " elements, "
    << "occupancy is " << occupancy << " elements.\n";
    
    /* go through all table elements */
    for (long index = 0; index < size; index++)
        if (table[index])
            table[index]->Write(stream << "at index "
                                << index << ":  ") << "\n";
    return stream;
}	/* end: Write */

