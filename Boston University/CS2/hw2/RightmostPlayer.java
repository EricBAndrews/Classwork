package hw2;

public class RightmostPlayer extends Player {

    public RightmostPlayer(int t) {
	super(t);
    }

    @Override
    int nextMove(Board board) {
	int move = board.rightMostUnfilledColumn();
	return move;
    }

}
