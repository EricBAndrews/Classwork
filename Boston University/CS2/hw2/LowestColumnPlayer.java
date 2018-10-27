package hw2;

public class LowestColumnPlayer extends Player {

    public LowestColumnPlayer(int t) {
	super(t);
    }

    @Override
    int nextMove(Board board) {
	int move = board.lowestColumn();
	return move;
    }

}
