package hw7;

import java.util.*;

public class TernarySearchTree implements Iterable<String> {

    private TernaryTreeNode root;

    public TernarySearchTree() {
	this.root = null;
    }

    public static TernarySearchTree GetTestTree() {
	TernarySearchTree t = new TernarySearchTree();
	t.root = new TernaryTreeNode('c');
	t.root.left = new TernaryTreeNode('a');
	t.root.center = new TernaryTreeNode('u');
	t.root.right = new TernaryTreeNode('h');
	t.root.left.center = new TernaryTreeNode('t');
	t.root.center.center = new TernaryTreeNode('t');
	t.root.right.center = new TernaryTreeNode('e');
	t.root.right.right = new TernaryTreeNode('u');
	t.root.left.center.left = new TernaryTreeNode('s');
	t.root.center.center.left = new TernaryTreeNode('p');
	t.root.center.center.center = new TernaryTreeNode('e');
	t.root.right.right.left = new TernaryTreeNode('i');
	t.root.right.right.center = new TernaryTreeNode('s');
	return t;
    }

    public boolean contains(String s) {
	TernaryTreeNode cur = root;
	int i = 0;
	while (i != s.length()) {
	    if (s.charAt(i) < cur.splitChar) {
		if (cur.left == null) {
		    break;
		}
		cur = cur.left;
	    }
	    else if (s.charAt(i) > cur.splitChar) {
		if (cur.right == null) {
		    break;
		}
		cur = cur.right;
	    }
	    else {
		if (cur.center == null) {
		    return (i == (s.length() - 1));
		}
		i++;
		cur = cur.center;
	    }
	}
	return false;
    }

    public void add(String s) {
	int i = 0;
	if (root == null) {
	    root = new TernaryTreeNode(s.charAt(0));
	}
	TernaryTreeNode cur = root;
	while (i < s.length()) {
	    if (s.charAt(i) == cur.splitChar) {
		i++;
		if (i == s.length()) {
		    break;
		}
		if (cur.center == null) {
		    cur.center = new TernaryTreeNode(s.charAt(i));
		}
		cur = cur.center;
	    }
	    else if (s.charAt(i) < cur.splitChar) {
		if (cur.left == null) {
		    cur.left = new TernaryTreeNode(s.charAt(i));
		}
		cur = cur.left;
	    }
	    else {
		if (cur.right == null) {
		    cur.right = new TernaryTreeNode(s.charAt(i));
		}
		cur = cur.right;
	    }
	}
	return;
    }

    class TSTiterator implements Iterator<String> {

	Stack<TernaryTreeNode> Nodes = new Stack<TernaryTreeNode>();
	Stack<String> Prefs = new Stack<String>();
	TernaryTreeNode n;
	String p;

	TSTiterator() {
	    Nodes.push(root);
	    Prefs.push("");
	}
		
	public String next() {
	    if (!hasNext()) {
	    	throw new NoSuchElementException();
	    }
	    while (true) { // risky but makes the logic work
		n = Nodes.pop();
		p = Prefs.pop();
		if (n == null) {
		    return p;
		}
		if (n.right != null) {
		    Prefs.push(p);
		    Nodes.push(n.right);
		}
		Prefs.push(p + n.splitChar);
		Nodes.push(n.center);
		if (n.left != null) {
		    Prefs.push(p);
		    Nodes.push(n.left);
		}
	    }
	}
		
	public boolean hasNext() {
	    return !Nodes.isEmpty();
	}
		
	public void remove(){
	    throw new UnsupportedOperationException();
	}

    }
    /*
     * Do not modify this method
     * 
     * @see java.lang.Iterable#iterator()
     */
    @Override
    public Iterator<String> iterator() {
	return new TSTiterator();
    }

    public String toString () {
	Stack<TernaryTreeNode> Nodes = new Stack<TernaryTreeNode>();
	Stack<String> Prefs = new Stack<String>();
	String ret = "";
	Nodes.push(root);
	Prefs.push("");
	TernaryTreeNode n;
	String p;
	while (!Nodes.isEmpty()) {
	    n = Nodes.pop();
	    p = Prefs.pop();
	    if (n == null) {
		ret += p + "\n";
	    }
	    else {
		if (n.right != null) {
		    Prefs.push(p);
		    Nodes.push(n.right);
		}
		Prefs.push(p + n.splitChar);
		Nodes.push(n.center);
		if (n.left != null) {
		    Prefs.push(p);
		    Nodes.push(n.left);
		}
	    }
	}
	return ret;
    }
}
