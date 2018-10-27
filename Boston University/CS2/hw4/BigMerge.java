package hw4;

public class BigMerge {
    // returns lowest topval of 2-d array a
    public static int argMin(int[][] a, int[] index) {
	int i;
	int min = 0;
	int minIndex = 0;
	for (i = 0; i < index.length; i++) {
	    if (index[i] < a[i].length) {
		min = a[i][index[i]];
		minIndex = i;
		break;
	    }
	}
	for (i = 0; i < a.length; i++) {
	    if ((index[i] < a[i].length) && (a[i][index[i]] < min)) {
		min = a[i][index[i]];
		minIndex = i;
	    }
	}
	return minIndex;
    }
    // performs the merge
    public static int[] merge (int[][] a) {
	// merges a 2-d array, returns the result
	int retLen = 0;
	int i;
	for (i = 0; i < a.length; i++) {
	    retLen += a[i].length;
	}
	int[] index = new int[a.length];
	int[] ret = new int[retLen];
	for (i = 0; i < retLen; i++) {
	    int minIndex = argMin(a, index);
	    ret[i] = a[minIndex][index[minIndex]];
	    index[minIndex]++;
	}
	return ret;
    }
}














  //            *     ,MMM8&&&.            *
  //                 MMMM88&&&&&    .
  //                MMMM88&&&&&&&
  //    *           MMM88&&&&&&&&
  //                MMM88&&&&&&&&
  //                'MMM88&&&&&&'
  //                  'MMM8&&&'      *
  //         |\___/|
  //         )     (             .              '
  //        =\     /=
  //          )===(       *
  //         /     \
  //         |     |
  //        /       \
  //        \       /
  // _/\_/\_/\__  _/_/\_/\_/\_/\_/\_/\_/\_/\_/\_
  // |  |  |  |( (  |  |  |  |  |  |  |  |  |  |
  // |  |  |  | ) ) |  |  |  |  |  |  |  |  |  |
  // |  |  |  |(_(  |  |  |  |  |  |  |  |  |  |
  // |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
  // |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
