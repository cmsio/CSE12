/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW6 
 * File name: HashTable.java 
 * Description: We are leaning Hash table in this assignment, and 
 *              it can allow variable assignment to the calculator
 *              we use bully algorithm to make probing
 */

public class HashTable extends Base {

	/* counters, flags and constants */
	private static int counter = 0; // number of HashTables so far
	private static boolean debug; // allocation of debug states
	protected static final short NULL = 0; // in case you want to use NULL

	/* data fields */
	private long occupancy; // number of items stored in table
	private int size; // size of hash table
	private Base table[]; // the Hash Table itself ==> array of Base
	private int tableCount; // which hash table it is

	/* initialized by Locate function */
	private int index; // last location checked in hash table

	/* debug messages */
	private static final String DEBUG_ALLOCATE = " - Allocated]\n";
	private static final String DEBUG_INSERT = " - Insert]\n";
	private static final String DEBUG_LOCATE = " - Locate]\n";
	private static final String DEBUG_LOOKUP = " - Lookup]\n";
	private static final String FULL = " is full...aborting...]\n";
	private static final String HASH = "[Hash Table ";
	private static final String HASH_VAL = "[Hash value is: ";
	private static final String INSERT_BUMP = "[bumping to next location...]\n";
	private static final String PROCESSING = "[Processing ";
	private static final String TRYING = "[Trying index ";;

	/**
	 * turn on debug message. turn off
	 */
	public static void setDebugOff() {
		debug = false;
	}

	/**
	 * method name: setDebugOn
	 * turn on debug message. turn on 
	 */
	public static void setDebugOn() {
		debug = true;
	}

	/**
	 * method name: HashTable
	 * Allocate and initial memory. Allocates and initializes the memory
	 * associated with a hash table. I use the while loop to increment index
	 *
	 * @param sz
	 *        sz can be any positive prime
	 */
	public HashTable(int sz) {
    // allocate memory to table
		table = new Base[sz];
		// for counting the occupancy
		occupancy = 0;
		size = sz;
		index = 0;
		tableCount = ++counter;

    // when the index is less then the size 
		while (index < sz) {
      // table index = null
			table[index] = null;
			index++;
    }
    // print the debug message
		if (debug) {
			System.err.println(HASH + tableCount + DEBUG_ALLOCATE);
		}
  }

	/**
	 * method name: insert
	 * Performs insertion into the tabble via delegation to the private insert
	 * method. reset the index when return false
	 *
	 * @param element
	 *            calculate the index and return to insert
	 * @return insert(element,false)
	 */
	public boolean insert(Base element) {
    index = element.hashCode() % size;
		return insert(element, false);
	}

	/**
	 * method name: insert
	 * Inserts the element in the hash table. If the element cannot be inserted,
	 * false will be returned. If the element can be inserted, the element is
	 * inserted and true is returned. Duplicate insertions will cause the
	 * existing element to be deleted, and the duplicate element to take its
	 * place.
	 *
	 * @param element
	 *						it is complete elements to insert
	 * @param recursiveCall
	 *            Checking whether this function is called recursively
	 * @return false when the called from Driver's main, otherwise, true
	 */
	private boolean insert(Base element, boolean recursiveCall) {

		if (debug) {
      System.err.print(HASH + tableCount + DEBUG_INSERT);
		}
    // use this variable to store the locate function
    Base temportory_location = locate(element);
		// it is use for store the table index
		Base temportory_base;


    // if the occupancy = size, it is full
		if (occupancy == size) {
      if (debug) {
        System.err.println(FULL);
      }
			return false;
		}

    // if temportory_ location is null
		if (temportory_location == null) {
			if (table[index] == null) {
				table[index] = element;
				occupancy++;
				return true;
			}
			else {
				// set the recursiveCall is true
				recursiveCall = true;
				temportory_base = table[index];
				table[index] = element;

        // this variable store the after increment
				int increment = (element.hashCode() % (size - 1)) + 1;
				// it is for calculate determining the next location
				index = (index + increment) % size;
				
				if (debug) {
					System.err.println(INSERT_BUMP);

				}
				// recursiveCall the insert method
				return insert(temportory_base, recursiveCall);
      }
    }
		// if the location is not equal null
		else if (temportory_location != null) {
      table[index] = element;
		}
		else {
			return false;
		}

		return true;
  }

	/**
	 * method name locate
	 * Find the location in the hash table. We separate four cases to know 
	 * what's the location the element can insert. If table[index] equal null
	 * we know that the array is null, so return null. If it is less than 
	 * element, we know that the element can not be pop out. So, we need to
	 * return null again. if it is equal, it suppose to be return element.
	 * And then every times the while loop run, we need to keep tracking
	 * how mant times the program run.
	 *
	 * @param element 
	 *						complete and incomplete elements depend on call insert or 
	 *						loop up
	 * @return null or element
	 */
	private Base locate(Base element) {
    // this variable is for increment
		int increment = (element.hashCode() % (size - 1)) + 1;

		if (debug) {
			System.err.print(HASH + tableCount + DEBUG_LOCATE);
			System.err.println(PROCESSING + element.getName() + "]");
			System.err.println(HASH_VAL + element.hashCode() + "]");
		}
		int counter = 0;

    // while the counter is less then size
		while (counter < size) {
			if (debug) {
				System.err.println(TRYING + index);
			}
      // if the table[index] =0
			if (table[index] == null) {
				return null;
			}
      // if the table[index] less than element
			if (table[index].isLessThan(element)) {
				return null;
			}
      // if the table[index] equals element
			if (table[index].equals(element)) {
				return element;
			}
      // calculate the next location
			index = (index + increment) % size;
			counter++;
		}

		return null;
	}

	/**
	 * method name: look up
	 * Find the location to look up. if the location is empty
	 * we need to return table[index], otherwise, return null
	 *
	 * @param element
	 *            incomplete elements to look up
	 * @return table[index] or null
	 */
	public Base lookup(Base element) {
		if (debug) {
			System.err.print(HASH + tableCount + DEBUG_LOOKUP);
		}
    // calculate the initilize location
		index = element.hashCode() % size;
		//if locate is not equal null
		if (locate(element) != null) {
			return table[index];
		} 
		else {
      return null;
		}
	}

	/**
	 * method name: toString
	 * Creates a string representation of the hash table. The method traverses
	 * the entire table, adding elements one by one according to their index in
	 * the table.
	 *
	 * @return String representation of hash table
	 */
	public String toString() {

		String string = "Hash Table " + tableCount + ":\n";
		string += "size is " + size + " elements, ";
		string += "occupancy is " + occupancy + " elements.\n";

		/* go through all table elements */
		for (int index = 0; index < size; index++) {

			if (table[index] != null) {
				string += "at index " + index + ":  ";
				string += "" + table[index] + "\n";
			}
		}

		return string;
	}
}
