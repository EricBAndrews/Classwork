package hw2;
import java.util.Scanner;

public class HumanPlayer extends Player {

    private Scanner sc; 
	
    public HumanPlayer(int t) {
	super(t);
	sc = new Scanner(System.in);
    }
	
    @Override
    int nextMove(Board board) {
	System.out.print(Board.sym[type] + ", your move? ");
	int move;
	do {
	    move = sc.nextInt();
	} while ((move >= board.getWidth()) |
		 (move < 0) |
		 !(board.canAddTo(move)));
	return move;
    }
}
