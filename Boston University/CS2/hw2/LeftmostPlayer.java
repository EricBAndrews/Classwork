package hw2;

public class LeftmostPlayer extends Player {

    public LeftmostPlayer(int t) {
	super(t);
    }

    @Override
    int nextMove(Board board) {
	int move = board.leftMostUnfilledColumn();
	return move;
    }

}
