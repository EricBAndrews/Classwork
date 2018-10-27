package driver;

import a1.BinarySearchVariant;

/******
 * @author: Eric Andrews
 * @email: ericandr@bv.edu
 ******/
public class BinarySearchVariantDriver {
    
    public static void main(String[] args) {
	// problem 1 test
	System.out.println("testing problem 1...");
	int passed = 0;
	int i;
	int answer;
	int guess;
	for (i = 0; i < 4096; i++) {
	    answer = (int) Math.floor(Math.sqrt(i));
	    guess = BinarySearchVariant.problem1(i);
	    if (answer != guess) {
		System.out.println("failure at " + i);
	    }
	    else { passed ++; }
	}
	System.out.println("passed " + passed + "/" + i + " tests\n");

	// problem 2 test
	int arrayOfInt[] = {0, 1, 2, 0};
	System.out.println(BinarySearchVariant.problem2(arrayOfInt));
    }
    
}
