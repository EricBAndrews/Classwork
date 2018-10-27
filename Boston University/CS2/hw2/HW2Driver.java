package hw2;

class HW2Driver {
    public static void main (String [] args) {
	//System.out.println("testing...");
	Player p1 = new HumanPlayer(1);
	Player p2 = new HumanPlayer(2);
	int result = Game.play(3, 3, 3, p1, p2);
	switch (result) {
	case 0: System.out.println("tie! board is full.");
	    break;
	case 1: System.out.println("player 1 wins!");
	    break;
	case 2: System.out.println("player 2 wins!");
	    break;
	}
    }
}
