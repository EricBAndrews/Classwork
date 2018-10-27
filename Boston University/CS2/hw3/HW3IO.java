package hw3;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

public class HW3IO {

    private static boolean checkAlphaOrder(String [] dict) {
	int i;
	if ((dict.length <= 1) && (dict.length >=0)) { return true; }
	for (i = 1; i < (dict.length - 1); i++) {
	    if (dict[i].compareTo(dict[i + 1]) > 0) { return false; }
	}
	return true;
    }
    
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

    private static boolean checkIfRectangle(char [][] board) {
	if (board.length == 0) { return true; }
	int i;
	int baseLen = board[0].length;
	for (i = 0; i < board.length; i++) {
	    if (board[i].length != baseLen) { return false; }
	}
	return true;
    }

    public static char[][] readBoard (String boardFileName) {
	Scanner fileScanner;
	// open the board file
	try {
	    fileScanner = new Scanner (new File (boardFileName));
	}
	catch (IOException e) {
	    System.out.println("Unable to open board file "+e.getMessage());
	    System.out.println("Currently in directory "+ System.getProperty("user.dir"));
	    return null;
	}

	// read the board file
	LinkedList<char[]> prelimBoard = new LinkedList<char[]>();
	while (fileScanner.hasNext()) {
	    prelimBoard.add(fileScanner.next().toLowerCase().toCharArray());
	}
	char [][] board = prelimBoard.toArray(new char[0][]);
	fileScanner.close();
		
	if(checkIfRectangle(board)) {
	    return board;
	}
	else {
	    System.err.println("Error: board is not rectangular.");
	    return null;
	}
    }

}
