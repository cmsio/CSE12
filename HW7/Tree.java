/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW7
 * File name: Tree.java 
 * Description: We are leaning Tree in this assignment, and 
 *              it can allow we search the name from UCSDSTUDENT
 *              and.So we can remove, lookup, and insert
 */

public class Tree<Whatever extends Base> extends Base {

    /* data fields */
    private TNode root;
    private long occupancy; 
		private String treeName;

    /* debug flag */
		private static boolean debug;

    /* debug messages */
    private static final String ALLOCATE = " - Allocating]\n";
    private static final String AND = " and ";
    private static final String COMPARE = " - Comparing ";
    private static final String INSERT = " - Inserting ";
    private static final String TREE = "[Tree ";

    public Tree (String name) {
        treeName = name;
				occupancy =0;
				root = null;

        if (debug){
            System.err.print(TREE+ALLOCATE+ name);
        }
    }
    /*--------------------------------------------------------------------------
    Function Name:          debugOff
    Purpose:                turn off the debug message
    Input:                  nothing
    return:                 void
    --------------------------------------------------------------------------*/
    public static void debugOff () {
        debug = false;
    }
   
    /*--------------------------------------------------------------------------
    Function Name:          debugOn
    Purpose:                turn on the debug message
    Input:                  nothing
    return:                 void
    --------------------------------------------------------------------------*/
    public static void debugOn () {
        debug = true;
    }

    /**
     * Returns the tree's name
     * @return name of the tree
     */
    public String getName() {
        return treeName;
    }

    /*--------------------------------------------------------------------------
    Function Name:          insert
    Description:            I first use the if statement to check is root empty
                            then check whether it NULL.
    Purpose:                insert element in binary tree
    Input:                  
        element             expect to be completes to insert
    return:                 true or false
    --------------------------------------------------------------------------*/
    public boolean insert (Whatever element) {
				// using the current to store root
        TNode current = root; 
        if (debug){
				    System.err.println(TREE+ treeName+ INSERT+ element.getName()+"]");
				}
				// if the root is null
				if (root == null){
            root = new TNode(element);
				}
				else{
				    while(true){
								if (debug){
                    System.err.println(TREE +treeName + COMPARE
								    +element.getName()+ " and " + current.data.getName()+ "]");
                }
				        //duplicate insert check
				        if(current.data.equals(element)){
                    current.data = element;
										// check whether current has been deleted
								    current.hasBeenDeleted = false;
								    return true;
                }
                // if the current is less than
								else if (element.isLessThan(current.data)){

                    if (current.left == null){
												// current new TNode in left side
                        current.left = new TNode(element);
										    current.left.parent =current;
										    current = current.left;
										    break;
								    }
								    else{
                        current = current.left;
								    }
                }
								// else the current is grether 
				        else{
                    if(current.right == null){
												// create new TNode in right side
								        current.right = new TNode(element);
										    current.right.parent = current;
										    current = current.right;
										    break;
								    }
								    else{
                        current = current.right;
								    }
				        }
            }
        }
				// increment occupancy
        occupancy++;
				// while current is not null and current parent is not null
		    while(current != null && current.parent !=null){
				    // set the leftheight
            long leftHeight =-1;
						// set the right height
				    long rightHeight =-1;
				    current = current.parent;
						// if current left is not null
				    if(current.left != null){
                leftHeight = current.left.height;
				    }
				    if(current.right != null){
                rightHeight = current.right.height;
				    }
						// Calculate the max
				    current.height = 1+ Math.max(leftHeight, rightHeight);
				    current.balance = leftHeight-rightHeight;
        }
				// return true
		    return true;
    }

        
    /*--------------------------------------------------------------------------
    Function Name:          lookup
    Description:            While the current is not null, and check for equal 
                            lessthan, and greather
    Purpose:                look at the element
    Input:                  
        element             expect to be completes to look up
    return:                 null and current data
    --------------------------------------------------------------------------*/

    public Whatever lookup (Whatever element) {
				
        // create a temportory variable
        TNode current = root;
				// while the current is not equal root
				while (current!= null){

				    if (debug){
                System.err.println(TREE + treeName+ COMPARE+
				        element.getName()+" and "+current.data.getName()+ "]");
            }

            if (element.equals(current.data)){
								// if current hasbeendeleted 
								if (current.hasBeenDeleted == true){
								    // return null
                    return null;
								}
								else{
								    // return current data
                    return current.data;
								}
				    }
						// if element is less than current
            else if(element.isLessThan(current.data)){
                current = current.left;
				    }
						// if element is greather than current
				    else{
                current = current.right;

				    }
        }
        return null;
    }

    /*--------------------------------------------------------------------------
    Function Name:          remove
    Description:            I first use while to test whether the current 
		                        is null or not, and check whether the element 
														is equal,less than, or greater 
														than the current data. we need to
														also use the hasbeendeleted 
    Purpose:                remove element
    Input:                  
        element             expect to be completes to remove
    return:                 null
    --------------------------------------------------------------------------*/

    public Whatever remove (Whatever element) {
				// create a temportory cariable
        TNode current = root;
				// to save the current 
				Whatever save_current;
				// while the current is not equal root
        while (current != null){
				    if (debug){
                System.err.println(TREE + treeName+ COMPARE+
				        element.getName()+" and "+current.data.getName()+ "]");
            }
        
            // if the element is equal current
				    if (element.equals(current.data)){
								if (current.hasBeenDeleted== true){
                    return null;
								}
								else{
                    current.hasBeenDeleted = true;
										// Drecrement occupancy
										occupancy --;
                    save_current = current.data;
										return save_current;
								}
        
				    }
						// if the element is less than
				    else if (element.isLessThan(current.data)){
                current = current.left;
				    }
						// else is greather than 
				    else{
                current = current.right;
        
				    }
        }
        return null;
    }

  /**
   * Creates a string representation of this tree. This method first
   * adds the general information of this tree, then calls the
   * recursive TNode function to add all nodes to the return string 
   *
   * @return  String representation of this tree 
   */

    public String toString(){
				String string = "Tree " + treeName + ":\noccupancy is "; 
        string += occupancy + " elements.";

        if(root != null)
            string += root.writeAllTNodes();

        return string;
    }
    /*
		 * this class is to create TNode
		 */
    private class TNode {
        public Whatever data;
        public TNode left, right, parent;
        public boolean hasBeenDeleted;

        /* left child's height - right child's height */
        public long balance;
        /* 1 + height of tallest child, or 0 for leaf */
        public long height;


    /*--------------------------------------------------------------------------
    Function Name:          TNode
    Description:            Allocate memory
    Purpose:                initial memory with the TNode object
    Input:                  
        element             data store in TNode
    return:                 void
    --------------------------------------------------------------------------*/

    public TNode (Whatever element) {
				// data is element
        data=element;
				// left is null
				left = null;
				right = null;
				// parent is null
				parent = null;
				balance =0;
				height = 0;
				// has been deleted is false
				hasBeenDeleted = false;
    }

    /**
     * Creates a string representation of this node. Information
     * to be printed includes this node's height, its balance,
     * and the data its storing.
     *
     * @return  String representation of this node 
     */

    public String toString () {
        return "at height:  " + height + "  with balance: " +
        balance + "  " + data;
    }

    /**
     * Writes all TNodes to the String representation field. 
     * This recursive method performs an in-order
     * traversal of the entire tree to print all nodes in
     * sorted order, as determined by the keys stored in each
     * node. To print itself, the current node will append to
     * tree's String field.
     */

    public String writeAllTNodes () {
        String string = "";
        if (left != null)
            string += left.writeAllTNodes ();
        if (!hasBeenDeleted) 
            string += "\n" + this;          
        if (right != null)
            string += right.writeAllTNodes ();

        return string;
    }
  }
}
