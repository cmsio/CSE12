/**
 * Name: ChakMan Sio 
 * Class: CSE 12 
 * Account cs12xef
 * Quarter: Fall 2016 
 * Assignment: HW6 
 * File name: Driver.java 
 * Class Description: this class allow to accsss the UCSDStudent, I can 
 *                    use those functions to implement my HashTable.java
 */

import java.io.*;

class UCSDStudent extends Base {
        private String name;
        private long studentnum;
        
				public long value;
        public UCSDStudent (String nm, long val){
            name = new String (nm);
						value = val;
				}
				public UCSDStudent (Variable variable){
            name = new String (variable.name);
            value = variable.value;

				}

				public String getName(){
            return name;
        }

				public boolean equals (Object object){
            Base bbb = (Base) object;
				     return name.equals (bbb.getName ());
        }
				public boolean isLessThan (Base bbb) {
				    return (name.compareTo (bbb.getName ()) < 0) ? true : false;
				}
				public String toString () {
				    return "name: "+ name +" "+ "Studentnum: " + value ;
						                                                     
        }

				public int hashCode () {
				    int retval = 0;
            int index = 0;

				    while (index != name.length ()) {
				        retval += name.charAt (index);
								index ++;
				    }

				    return retval;
        }
}

public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
                /* initialize debug states */
                HashTable.setDebugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                HashTable.setDebugOn();
                }

                /* The real start of the code */
                SymTab symtab = new SymTab (5);
                String buffer = null;
                char command;
                long number = 0;

                System.out.print ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = 0;    // reset command each time in loop
                        System.out.print ("Please enter a command:  "
                                + "((i)nsert, (l)ookup, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'i':
                                System.out.print (
                                "Please enter UCSD Student name to insert:  ");
                                buffer = MyLib.getline ();// formatted input

                                System.out.print (
                                        "Please enter UCSD Student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create Student and place in symbol table
                                if(!symtab.insert (
                                        new UCSDStudent (buffer, number))){

                                        System.out.print ("\nFinal Symbol "
                                                        + "Table:\n" + symtab);
                                        System.exit(0);
                                }
                                break;

                        case 'l': {
                                Base found;     // whether found or not

                                System.out.print (
                                "Please enter UCSD Student name to lookup:  ");

                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println ("Student found!!!");
                                        System.out.println (found);
                                }
                                else
                                        System.out.println ("Student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.print (
                                    "The Symbol Table contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }

                System.out.print ("\nFinal Symbol Table:\n" + symtab);
        }
}
