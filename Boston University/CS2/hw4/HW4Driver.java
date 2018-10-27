package hw4;

import java.io.File;

/*
 * TODO: THIS IS THE FILE FOR TESTING YOUR CODE -- 
 * DO WHATEVER YOU WANT HERE, IT WON'T BE GRADED
 */

public class HW4Driver {
    public static void testBigMerge() {
	int[][] a = {{1,2,3,7},{2,5,12},{2,6,8}};
	int[] b = BigMerge.merge(a);
	int i;
	for (i = 0; i < b.length; i++) {
	    System.out.println(b[i]);
	}
    }
    
    public static void testFindSpacing() {
	String dictionaryFileName = "hw4"+File.separatorChar+"english_words.txt";
	String [] dict = HW4IO.readDictionary(dictionaryFileName);
	if (dict == null) return;
	String [] result = FindSpacing.space(dict, "becausetodayuseat");
	for (String w : result) {
	    System.out.println(w);
	}
    }
    
    public static void main(String[] args) {
	testBigMerge();
	testFindSpacing();
    }	
}
