package hw2;

/* * * *
 * @author: Eric Andrews
 * @email: ericandr@bu.edu
 * * * */

public class Board {
    // 0 means empty, 1 means X, 2 means O
    public static final char [] sym = {' ', 'X', 'O'};
    private int [][] board; /* It makes more sense to me to index this [column][row], so
			     * that's how I've implemented this (also it improves locality)
			     * I've adjusted the toString to not break.
			     */
    private int height, width;
    private int winLength;
    private int checkCount;

    public Board (int h, int w, int winLen) {
	height = h;
	width = w;
	winLength = winLen;
	board = new int [width][height]; // Swapped for above reasons
    }
	
    public int getWidth() { return width; }

    public int getHeight(int col) {
	int row = 0;
	while (board[col][row] != 0) {
	    if (row == (this.height - 1)) {
		return row;
	    }
	    row++;
	}
	return row;
    }

    public int leftMostUnfilledColumn() {
	int i;
	for (i = 0; i < this.width; i++) {
	    if (canAddTo(i)) { return i; }
	}
	return -1;
    }

    public int rightMostUnfilledColumn() {
	int i;
	for (i = (this.width - 1); i >= 0; i++) {
	    if (canAddTo(i)) { return i; }
	}
	return -1;
    }
    
    public int highestColumn() {
	int i;
	int highest = leftMostUnfilledColumn();
	for (i = highest; i < this.width; i++) {
	    if ((canAddTo(i)) & (getHeight(i) > getHeight(highest))) {
		highest = i;
	    }
	}
	return highest;
    }

    public int lowestColumn() {
	int i;
	int lowest = 0;
	for (i = 0; i < this.width; i++) {
	    if (getHeight(i) < getHeight(lowest)) {
		lowest = i;
	    }
	}
	return lowest;
    }
	
    public void addChecker (int type, int column) {
	int i;
	for (i = 0; i < this.height; i++) {
	    if (board[column][i] == 0) {
		board[column][i] = type;
		this.checkCount++;
		break;
	    }
	}
    }
		
    public boolean canAddTo (int column) {
	return ((board[column][this.height - 1] == 0) && (column < this.width));
    }
	
    public boolean isFull () {
	int maxSize = this.height * this.width;
	return (this.checkCount >= maxSize);
    }
	
    private boolean hasWonVertically (int type) {
	int col;
	int row;
	int numFound;
	for (col = 0; col < this.width; col++) {
	    numFound = 0;
	    for (row = 0; row < this.height; row++) {
		if (board[col][row] == type) { numFound++; }
		else { numFound = 0; }
		if (numFound == this.winLength) { return true; }
	    }
	}
	return false;
    }
	
    private boolean hasWonHorizontally (int type) {
	int col;
	int row;
	int numFound;
	for (row = 0; row < this.height; row++) {
	    numFound = 0;
	    for (col = 0; col < this.width; col++) {
		if (board[col][row] == type) { numFound++; }
		else { numFound = 0; }
		if (numFound == this.winLength) { return true; }
	    }
	}
	return false;
    }
	
    private boolean hasWonNW (int type) {
	int baseCol;
        int baseRow;
        int col;
        int row;
        int numFound;
	// Iterate across the bottom
	for (baseCol = this.winLength - 1; baseCol < this.width; baseCol++) {
	    numFound = 0;
	    for (col = baseCol, row = 0; col >= 0; col--) {
		if (board[col][row] == type) {
		    numFound++;
		    if (numFound == this.winLength) { return true; }
		}
		else { numFound = 0; }
		if (row < this.height) { row++; }
	    }
	}
	// Iterate up from 1 above the bottom-right corner
	baseCol = this.width - 1;
	for (baseRow = 1; baseRow <= (this.height - this.winLength); baseRow++) {
	    numFound = 0;
	    for (row = baseRow, col = baseCol; row < this.height; row++) {
		if (board[col][row] == type) {
		    numFound++;
		    if (numFound == this.winLength) { return true; }
		}
		else { numFound = 0; }
		if (col > 0) { col--; }
	    }
	}
	return false;
    }

    private boolean hasWonNE (int type) {
	int baseCol;
	int baseRow;
	int col;
	int row;
	int numFound;
	// Iterate across the bottom *right to left* (for reasons)
	for (baseCol = (this.width - this.winLength); baseCol >= 0; baseCol--) {
	    numFound = 0;
	    for (col = baseCol, row = 0; col < this.width; col++) {
		if (board[col][row] == type) {
		    numFound++;
		    if (numFound == this.winLength) { return true; }
		}
		else { numFound = 0; }
		if (row < (this.height - 1)) { row++; }
	    }
	}
	// Iterate up from 1 above the bottom-left corner
	baseCol = 0;
	for (baseRow = 1; baseRow <= (this.height - this.winLength); baseRow++) {
	    numFound = 0;
	    for (col = baseCol, row = 0; col < this.width; col++) {
		if (board[col][row] == type) {
		    numFound++;
		    if (numFound == this.winLength) { return true; }
		}
		else { numFound = 0; }
		if (row < (this.height - 1)) { row++; }
	    }
	}
	return false;
    }

	
    public boolean hasWon (int type) {
	return (hasWonVertically(type) || hasWonHorizontally(type) || hasWonNW(type)
		|| hasWonNE(type));
    }
	
	
    // DO NOT MODIFY THIS METHOD -- made it work w/ my backwards implementation, no other change
    public String toString() {
	String s = "";
	for (int j = height-1; j>=0; j--) {
	    for (int i = 0; i<width; i++) {
		s += "|"+sym[board[i][j]];
	    }
	    s+="|\n";
	}
	for (int j = 0; j<width; j++) {
	    s += "--";
	}
	s+="-\n";
	for (int j = 0; j<width; j++) {
	    s += " "+j%10;
	}
	s+="\n";
	return s;
    }

}
