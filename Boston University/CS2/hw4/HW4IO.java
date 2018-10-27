package hw4;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;


/*
 * DO NOT MODIFY THIS FILE -- WE DID IT ALL FOR YOU
 */

public class HW4IO {
	
    /*
     *  Returns true if and only if
     *  dict is in alphabetical order
     */
    private static boolean checkAlphaOrder(String [] dict) {
	// TODO replace the "return true" below
	// with a check that dict is in alphabetical order
	// Use compareTo method of the String class
	// (you may want to see https://docs.oracle.com/javase/8/docs/api/java/lang/String.html)
	//		
	// Empty dictionary and one-word dictionary
	// are considered okay
	for (int i=1; i<dict.length; i++) {
	    if (dict[i].compareTo(dict[i-1])<0) {
		System.out.println(i);
		return false;
	    }
	}
	return true;
    }

	
    /*
     * Reads in a dictionary file (one word per line) and checks if it's
     * in alphabetical order. Returns null in case of failure.
     */
    public static String[] readDictionary (String dictionaryFileName) {
	Scanner fileScanner;
		
	// Open the dictionary file
	try {
	    fileScanner = new Scanner (new File (dictionaryFileName));
	}
	catch (IOException e) {
	    System.err.println("Unable to open dictionary file. "+e.getMessage());
	    System.err.println("Currently in directory "+ System.getProperty("user.dir"));
	    return null;
	}

	// read the dictionary file
	LinkedList<String> prelimDict = new LinkedList<String>();
	while (fileScanner.hasNext()) {
	    prelimDict.add(fileScanner.next().toLowerCase());
	}
	String [] dict = prelimDict.toArray(new String[0]);
	fileScanner.close();
	if(checkAlphaOrder(dict)) {
	    return dict;
	}
	else {
	    System.err.println("Error: dictionary not in alphabetical order.");
	    return null;
	}
    }
	


}
