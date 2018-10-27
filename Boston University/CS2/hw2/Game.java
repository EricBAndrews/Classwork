package hw2;

public class Game {
    public static int play(int height, int width, int winLength, Player p1, Player p2) {
	Board b = new Board(height,width,winLength);
	System.out.println(b);
	while (true) {
	    System.out.println("X moves next.");
	    b.addChecker(1, p1.nextMove(b));
	    if (b.isFull()) { return 0; }
	    if (b.hasWon(1)) { return 1; }
	    System.out.println(b);
	    System.out.println("O moves next.");
	    b.addChecker(2, p2.nextMove(b));
	    if (b.isFull()) { return 0; }
	    if (b.hasWon(2)) { return 2; }
	    System.out.println(b);
	}
    }

}
