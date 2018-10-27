package hw3;
import java.io.*;

public class HW3Driver {

    public static void main(String[] args) {
	String dictionaryFileName = "hw3"+File.separatorChar+"dictionary.txt";
	String boardFileName = "hw3"+File.separatorChar+"board2.txt";

	String [] dict = HW3IO.readDictionary(dictionaryFileName);
	if (dict == null) return;
	char [][] board = HW3IO.readBoard(boardFileName);
	if (board == null) return;
	
	String [] result = FindWords.search(dict, board);
	for (String w : result) {
	    System.out.println(w);
	}
    }	
	
}
