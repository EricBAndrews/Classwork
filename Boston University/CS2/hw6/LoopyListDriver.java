package hw6;


// MODIFY AS NEEDED -- THIS FILE WON'T BE GRADED

public class LoopyListDriver {
    private static String getCorrectPrintOut(int totalLength) {
	if (totalLength == 0) return "[]";
	String s = "[";
	int i;
	for (i = 1; i<totalLength; i++) {
	    s+=i+", ";
	}
	s+=i+"]"; // last one is special, because it has no comma after
	return s;
    }

    public static void main (String [] args) {
	for (int loopLength = 0; loopLength<100; loopLength++) {
	    for (int prefixLength = 0; prefixLength<100; prefixLength++) {
		LoopyList l = new LoopyList (prefixLength, loopLength);
		System.out.println("Testing prefix length " + prefixLength +
				   " and loop length " + loopLength+" ");
		String loopLessString = getCorrectPrintOut(loopLength + prefixLength);
		if (loopLength == 0) {
		    if (l.isLoopy()) {
			System.out.println("Shouldn't be loopy");
		    }
		    if (l.straighten()) {
			System.out.println("Straighten succeeded when it should have failed");
		    }
		    if (!l.toString().equals(loopLessString)) {
			System.out.println("The list printout is incorrect:\n  " + l
					   + "\ninstead of\n  " + loopLessString);
		    }
		} else {
		    if (!l.isLoopy())
			System.out.println("Should be loopy");
		    if (!l.straighten()) {
			System.out.println("Straighten failed when it should have succeeded");
		    }
		    if (!l.toString().equals(loopLessString)) {
			System.out.println("The list printout is incorrect after straigtening:\n  "
					   + l + "\ninstead of \n  " + loopLessString);
		    }
		}
	    }
	}
    }
}
