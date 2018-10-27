package hw7;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class TextAnalyzerConsole {

    public static void main (String [] args) {
	Scanner fileScanner;
	Scanner inputScanner = new Scanner (System.in);
	String fileName = "/Users/ericandrews/desktop/Folders/Work/BUA/CS112/Work/assignments/AssignmentsEclipseProject/hw7/LordoftheRings.txt";
	// ON WINDOWS IT WOULD BE SOMETHING LIKE "C:\\users\\Document\\Jane Eyre.txt"
	String firstWord = ""; // set to "" in order to start at the beginning of the file
	String endWord = ""; // set to "" in order to go to the end of the file
		
	// Open the dictionary file
	try {
	    fileScanner = new Scanner (new File (fileName));
	}
	catch (IOException e) {
	    System.err.println("Unable to open input file. "+e.getMessage());
	    System.err.println("Currently in directory "+ System.getProperty("user.dir"));
	    inputScanner.close();
	    return;
	}
		
	TextAnalyzer ta = new TextAnalyzer();
	System.out.println(ta.readText(fileScanner, firstWord, endWord));
	fileScanner.close();

	System.out.print("Enter frequency range as two integers: ");
		
	while (inputScanner.hasNext()) {
	    int from = inputScanner.nextInt();
	    int to = inputScanner.nextInt();
	    System.out.println(ta.printWords(from, to));
	    System.out.print("Enter frequency range as two integers: ");
	}
	inputScanner.close();
    }
}
