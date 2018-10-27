package hw7;

/**
 * TextAnalyzer.java
 * Boston University CAS CS 112 HW7
 * By Leo Reyzin
 */

import java.util.*;


public class TextAnalyzer {

    private CountingTree ctree;
    private BSTWithDuplicates ftree;

	
    /*
     * Reads words from fileScanner, starting at the first occurrence
     * of firstWord (inclusive) until the first occurrence of endWord
     * after that (exclusive).  If firstWord is the empty string,
     * starts at the beginning of the file.  If
     * endWord is the empty string, goes until the end
     * of the file.
     * 
     * Builds a binary search 
     * tree indexed by words that has a count of how many times
     * each word occurs, and another binary search tree indexed by
     * count that has all the words that appear a given number of times.
     * 
     * Returns a string to be output to the user.
     */
    public String readText (Scanner fileScanner, String firstWord, String endWord) {
	String ret = "";
		
	// This will make sure we read only words, no spaces, numbers, punctuation, etc.
	// Unfortunately, apostrophes and hyphens are considered delimiters
	// here (have to be, in order for quotes and dashes to work correctly)
	// which means that words with apostrophes and hyphens get split,
	// rather than taken as single words 
	fileScanner.useDelimiter("[^a-zA-Z]+");

	String word = null;

	// Skip all the text until firstWord appears
	if (!firstWord.equals("")) {
	    boolean found = false;
	    while (fileScanner.hasNext()) {
		word = fileScanner.next();
		if (word.equals(firstWord)) { // found the first word -- don't forget to insert it into the tree below
		    found = true;
		    break;
		}
	    }

	    if (!found) {
		ret+="First word not found.\n";
		ctree = null;
		ftree = null;
		return ret;
	    }
	}
		
	// first word is empty, so we need to start reading at the beginning
	else {
	    if (!fileScanner.hasNext()) {
		ret+="No words found.\n";
		ctree = null;
		ftree = null;
		return ret;
	    }
	    word = fileScanner.next(); // read the first word -- it has to be treated separately, because the code when firstWord is not empty will read it
	}

	// Insert all of the words in to the tree, converting them to lowercase first
	ctree = new CountingTree();
	boolean found = false;
	boolean endWordExists = !endWord.equals("");

	ctree.insert(word.toLowerCase()); // insert the first word		
	while (fileScanner.hasNext()) {
	    word = fileScanner.next();
	    if (endWordExists && word.equals(endWord)) {
		ret+="End word found.\n";
		found = true;
		break;
	    }
	    ctree.insert(word.toLowerCase());
	}
	if (endWordExists && !found) {
	    ret+="End word NOT found; end of file reached.\n";
	}
	ret+="\nTotal Words: "+ctree.getTotalEntries()+".";
	ret+="\nDistinct Words: "+ctree.getDistinctEntries()+".";

	ftree = ctree.frequencyTree();
	ret+="\nMost Frequent Word Appears "+ftree.maxKey()+" times.";
	ret+="\nYou may now search for all the words appearing within a range of frequencies.";
	return ret;
    }
	
    /*
     * Returns a string containing, one per line, all the words that appear
     * between low and high number of times in the analyzed text.
     * First line of the strings tells how many such words have been found.
     * Next to each word is its frequency.
     * The string is meant to be output to the user.
     * If readText has not been run or has not found any words in the text,
     * returns an error message.
     */

    public String printWords (int low, int high)
    {
	if (ftree == null)
	    return "No text has been analyzed.\n";

	String ret = "";
	Collection<String> result =  ftree.rangeSearch(low, high);
	ret+="Found "+result.size()+" words.\n";
	for (String s:result) {
	    // looking up the frequency of s in ctree is not the most
	    // efficient way to do this -- it would be more efficient
	    // to have the collection contain (word,frequency) pairs
	    // But that would slow down the rangeSearch, and the user
	    // may not always want to print out the results, anyway.  Besides,
	    // the extra time for lookup is small compared to user interaction
	    // time.
	    ret+=String.format("%5d %s\n",ctree.search(s),s);
	}
	return ret;
    }



}


