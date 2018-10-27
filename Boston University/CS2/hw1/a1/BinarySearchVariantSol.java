package a1;

/**
 * @author: ENTER YOUR FIRST AND LAST NAME HERE
 * @email: ENTER YOUR BU EMAIL HERE
 *
 *YOU MAY ADD EXTRA HELPER METHODS TO THIS CLASS.
 */
public class BinarySearchVariantSol {


  /**
   * @param a is an array of integers.
   * @return k that is the apex of the array.
   */
  public static int problem2(int[] a) {
		int begin = 0;
		int end = a.length;

		/* loop invariant: the location I need to return is
		 * somewhere between begin and end-1 
		 */
		while (begin+1<end) {
			int mid = (begin+end)/2;
			if (mid>0) { 
				if((mid > 0 && a[mid]>a[mid-1]) || (mid==0 && a[0]<a[1])) { //  mid is the apex or earlier
					begin = mid;
				}
				else {
					end = mid;
				}
			}
		}
		return begin;

  }

  /**
   * @param n>=1 is the number that you like to find the square root of.
   * @return back an int representation of the calculated squareroot.
   */
  public static int problem1(int n) {
		int begin = 0;
		int end = n+1;

		/* loop invariant: the value I need to return is
		 * somewhere between begin and end-1 
		 */ 	
		while (begin+1<end) {
			int mid = (begin+end)/2;
			if(mid*mid<=n) {
				begin = mid;
			}
			else {
				end = mid;
			}
		}
		return begin;
  }
}
