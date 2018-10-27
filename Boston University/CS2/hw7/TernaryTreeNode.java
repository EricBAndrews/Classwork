package hw7;

public class TernaryTreeNode {

    TernaryTreeNode left;
    TernaryTreeNode right;
    TernaryTreeNode center;
    char splitChar;

    public TernaryTreeNode(char c)
    {
	left = null;
	center = null;
	right = null;

	splitChar = c;
    }
}
