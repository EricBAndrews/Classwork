package hw4;

import java.util.LinkedList;

public class FindSpacing {
    // checks if s in in dict
    private static boolean inDictionary(String[] dict, String s) {
	int begin = 0;
	int end = dict.length - 1;
	while (begin<=end) {
	    int mid = (begin+end)/2;
	    int res = dict[mid].compareTo(s);
	    if (res == 0) {
		return true;
	    }
	    else if(res<0) {
		begin = mid+1;
	    }
	    else {
		end = mid -1;
	    }
	}
	return false;
    }
    // finds all possible spacing combinations
    public static String[] space (String[] dict, String s) {
	LinkedList<String> ret = new LinkedList<String>();
	// base case
	if (s.length()==0) {
	    String[] r = {""};
	    return r;
	}
	// recursive case
	int i;
	int j;
	String[] toAdd;
	for (i = 0; i <= s.length(); i++) {
	    if (inDictionary(dict, s.substring(0, i))) {
		toAdd = space(dict, s.substring(i));
		for (j = 0; j < toAdd.length; j++) {
		    ret.add(s.substring(0, i) + " " + toAdd[j]);
		}
	    }
	}
	// This line converts LinkedList<String> to String[]
	return ret.toArray(new String[0]);
    }
}
