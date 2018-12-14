/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW7
 * File name: Driver.java
 * Class Description: this class allow to accsss the UCSDStudent, I can 
 *                    use those functions to implement my Tree.java
 */


import java.io.*;

class UCSDStudent extends Base {

        private String name;
        private long studentnum;

        public long value;              /* value of interest */

        public UCSDStudent (String nm, long val) {
                name = new String (nm);
                value = val;
        }
        public UCSDStudent (UCSDStudent  variable) {
                name = new String (variable.name);
                value = variable.value;
        }

        public String getName () {
                return name;
        }
        public boolean equals (Object object) {
		        if (this == object)
			          return true;

		        if (!(object instanceof UCSDStudent ))
			          return false;
		
		        UCSDStudent  otherVar = (UCSDStudent) object;
		
		        return name.equals (otherVar.getName ());
        }
        public boolean isLessThan (Base base) {
                return (name.compareTo (base.getName ()) < 0) ? true : false;
        }
        public String toString () {
                return "name: "+name+ " " + "Studentnum: " + value;
        }

        public UCSDStudent  assignValue (long val) {
                
                UCSDStudent  retval;        // return value

                // give variable its value
                value = val;
                retval = new UCSDStudent  (this);

                return retval;
        }

}

public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
        
                /* initialize debug states */
                Tree.debugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                Tree.debugOn();
                }

                /* The real start of the code */
                SymTab<UCSDStudent> symtab = 
                        new SymTab<UCSDStudent>("UCSDStudentTree");
                String buffer = null;
                char command;
                long number = 0;

                System.out.println ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = NULL; // reset command each time in loop
                        System.out.print ("Please enter a command:  " + 
                                "((a)llocate, (i)nsert, (l)ookup, " +
                                "(r)emove, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {

                        case 'a':
                                System.out.print
                                        ("Please enter name of new Tree to " +
                                         "allocate:  ");
                                
                                buffer = MyLib.getline ();// formatted input
                                symtab = new SymTab<UCSDStudent>(buffer);
                                break;

                        case 'i':
                                System.out.print
                                ("Please enter UCSD student name to insert:  ");

                                buffer = MyLib.getline ();// formatted input

                                System.out.print
                                        ("Please enter UCSD student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create student and place in symbol table
                                symtab.insert(new UCSDStudent (buffer, number));
                                break;

                        case 'l': { 
                                UCSDStudent found;      // whether found or not

                                System.out.print
                                ("Please enter UCSD student name to lookup:  ");
                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println("Student found!!!");
                                        System.out.println(found);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!!!");
                                }
                                break;
                        
                        case 'r': { 
                                UCSDStudent removed; // data to be removed

                                System.out.print
                                ("Please enter UCSD student name to remove:  ");

                                buffer = MyLib.getline ();

                                UCSDStudent stu = new UCSDStudent (buffer, 0);

                                removed = symtab.remove(stu);

                                if (removed != null) {
                                        System.out.println("Student removed!"); 
                                        System.out.println(removed);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!!!");
                                }
                                break;

                        case 'w':
                                System.out.println("The Symbol Table " +
                                "contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }
                System.out.println("\nFinal Symbol Table:\n" + symtab);
        }
}
