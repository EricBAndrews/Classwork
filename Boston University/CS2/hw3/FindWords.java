package hw3;
import java.util.LinkedList;

public class FindWords {

    private static boolean inDictionary(String [] dict, String s) {
	int begin = 0;
	int end = dict.length - 1;
	int compare;
	int mid;
	while (begin < end) {
	    mid = (begin + end) / 2;
	    compare = dict[mid].compareTo(s);
	    if (compare == 0) { return true; }
	    else if (compare < 0) { begin = mid + 1; }
	    else { end = mid; }
	}
	return false;
    }
    
    public static String[] search(String[] dict, char[][] board) {
	LinkedList<String> ret = new LinkedList<String>();
	// fringe case of single-space board
	if ((board.length == 1) && (board[0].length == 1)) {
	    String toTest = "";
	    toTest += board[0][0];
	    if (inDictionary(dict, toTest)) {
		ret.add(toTest);
	    }
	}
	int height = board.length;
	int width = board.length==0 ? 0 : board[0].length;
	int i;
	int j;
	int iBase;
	int jBase;
	String testStringForwards; // left->right and top->bottom string
	String testStringBackwards; // right->left and bottom->top string
	// iterate right/left
	for (j = 0; j < height; j++) {
	    for (iBase = 0; iBase < (width - 1); iBase++) {
		testStringForwards = "";
		testStringBackwards = "";
		for (i = iBase; i < width; i++) {
		    testStringForwards += board[j][i];
		    testStringBackwards += board[j][(width - 1) - i];
		    if (inDictionary(dict, testStringForwards)) { ret.add(testStringForwards); }
		    if (inDictionary(dict, testStringBackwards)) { ret.add(testStringBackwards); }
		}
	    }
	}
	// iterate up/down
	for (i = 0; i < width; i++) {
	    for (jBase = 0; jBase < (height - 1); jBase++) {
		testStringForwards = "";
		testStringBackwards = "";
		for (j = jBase; j < height; j++) {
		    testStringForwards += board[j][i];
		    testStringBackwards += board[(height - 1) - j][i];
		    if (inDictionary(dict, testStringForwards)) { ret.add(testStringForwards); }
		    if (inDictionary(dict, testStringBackwards)) { ret.add(testStringBackwards); }
		}
	    }
	}
	// TODO (10% of your grade): if your board
	// has height h and width w, how many strings
	// do you need to check using inDictionary
	// (assume that you do nothing to filter out
	// duplicates or, equivalently, that the board
	// is such that there are no duplicates)
	// ANSWER: 2(hw^2 - 2hw + wh^2)
	// EXPLANATION OF THE ANSWER:
	    // inner loop 1 (right/left) iterates h * (w - 1) * w times, and checks two strings each loop
	    // inner loop 2 (up/down) iterates w * (h - 1) * h times, and checks two strings each loop
	    // therefore there are 2h(w^2 - w) + 2w(h^2 - h) checks
	    // which is the same as 2(hw^2 - 2hw + wh^2)

	// This line converts LinkedList<String> to String []
	return ret.toArray(new String[0]);
    }
}
