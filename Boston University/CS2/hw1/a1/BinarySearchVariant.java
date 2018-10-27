package a1;

/******
 * @author: Eric Andrews
 * @email: ericandr@bu.edu
 ******/
public class BinarySearchVariant {
    
    public static int problem2(int[] a) {
	int high = a.length - 1;
	int mid = high / 2;
	int low = 0;
	if (a.length == 1) { return 0; }
	while (low < high) {
	    // System.out.println("low: " + low + " mid: " + mid + " high: " + high);
	    if ((mid < a.length - 1) && (a[mid + 1] < a[mid])) {
		if (mid == 0) { return mid; }
		if (a[mid - 1] < a[mid]) { return mid;	}
		high = mid - 1;
	    }
	    else {
		if (mid == a.length - 1) { return mid; }
		low = mid + 1;
	    }
	    mid = (low + high) / 2;
	}
	return mid;
    }
    
    public static int problem1(int n) {
	int high = n;
        int low = 0;
	int mid = n / 2;
	while (low < high) {
	    // Fringe tests
	    if (Math.pow(low, 2) == n) { return low; }
	    if (Math.pow(mid, 2) == n) { return mid; }
	    if (Math.pow(high, 2) == n) {return high; }
	    // Splitting
	    if (Math.pow(mid, 2) > n) { high = mid - 1; }
	    else {
		if (Math.pow((mid + 1), 2) > n) { return mid; }
		low = mid + 1;
	    }
	    mid = (high + low) / 2;
	}
	return mid;
    }
}
