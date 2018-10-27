package hw2;

public class HighestColumnPlayer extends Player {

    public HighestColumnPlayer(int t) {
	super(t);
    }

    @Override
    int nextMove(Board board) {
	int move = board.highestColumn();
	return move;
    }

}
