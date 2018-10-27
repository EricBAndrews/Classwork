package hw7;

import java.util.*;

public class TernarySearchTreeDriver {

    public static void aFewTests() {
	String [] stringList = {"cute", "he", "cup", "at", "as", "us", "i"};
	TernarySearchTree tst = new TernarySearchTree();
	for (String s : stringList) {
	    tst.add(s);
	    System.out.println(tst+"-------");
	}
		
		
	for (String s : stringList) {
	    if (!tst.contains(s)) {
		System.out.println("Doesn't contain what it should");
	    }
	    if (tst.contains(s+"a") || tst.contains(s+"z") || tst.contains(s.substring(1)) ||
		tst.contains(s.substring(0,s.length()-1))) {
		System.out.println("Contains what it should not");
	    }
	}

	System.out.println("Iterator Test 1");
	for (String s : tst) {
	    /*
	     * This must print out all the strings in the ternary search tree (tst) 
	     * in alphabetical order.
	     */
	    System.out.println(s);
	}

	System.out.println("Iterator Test 2");
	for (String s : TernarySearchTree.GetTestTree()) {
	    /*
	     * This must print out all the strings in the ternary search tree (tst) 
	     * in alphabetical order.
	     */
	    System.out.println(s);
	}
    }
	
    public static void main(String[] args) {
	String [] stringList = {"cute", "he", "cup", "at", "as", "us", "i"};
	TernarySearchTree test = TernarySearchTree.GetTestTree();
	for (String s : stringList) {
	    if (test.contains(s)) {
		System.out.println("contains " + s);
	    }
	    else {
		System.out.println("does not contain " + s);
	    }
	}
	aFewTests();
	return;
    }
}
