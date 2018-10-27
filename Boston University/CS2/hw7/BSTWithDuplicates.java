package hw7;

import java.util.LinkedList;
import java.util.Random;
/**
 * Binary search tree, keyed by integers with String data, which
 * allows for insertion of the same key twice (or more), and will create
 * a new node for it each time.  The new node may be either to
 * the right or to the left of a higher node with the same
 * key; the direction for a duplicate key
 * is chosen at random, else duplicate keys
 * could create very long chains and hamper performance (or even
 * cause stack overflow errors on recursion).
 * Has a special search, which returns a LinkedList
 * of data for all the keys within range.
 * 
 * @author reyzin
 */

public class BSTWithDuplicates {
    private class TreeNode {
	int key;
	String data;
	TreeNode left, right;
	TreeNode(int k, String d) {
	    key = k; data = d; left = right = null; 
	}
    }

    private TreeNode root = null;
    Random random = new Random();

    public static LinkedList<Long> times = new LinkedList<Long>();

    /**
     * Adds (key, data) pair to the tree, even if the same key
     * already exists.
     * @param key
     * @param data
     */
    public void insert (int key, String data) {
	// RECURSIVE IMPLEMENTATION
	root = insert(key, data, root);

	// ITERATIVE IMPLEMENTATION
	// worked out to about the same average runtime, but more lines so scrapped
    }
			 
    //  RECURSIVE HELPER
    private TreeNode insert (int key, String data, TreeNode subtree) {
    	if (subtree == null) {
    	    subtree = new TreeNode(key, data);
    	}
    	else if (key == subtree.key) {
    	    if (random.nextBoolean()){
    		subtree.left = insert(key, data, subtree.left);
    	    }
    	    else {
    		subtree.right = insert(key, data, subtree.right);
    	    }
    	}
    	else if (key < subtree.key) {
    	    subtree.left = insert(key, data, subtree.left);
    	}
    	else {
    	    subtree.right = insert(key, data, subtree.right);
    	}
    	return subtree;
    }

    /**
     * Assumes low<=high
     * 
     * @param low
     * @param high
     * @return a collection of all data elements whose keys are between low and high (inclusive)
     */
    public LinkedList<String> rangeSearch (int low, int high) {
	LinkedList<String> ret = new LinkedList<String>();
	rangeSearch (root, low, high, ret);
	return ret;
    }

    private void rangeSearch (TreeNode subtree, int low, int high, LinkedList<String> ret) {
	if (subtree == null) {
	    return;
	}
	if (high < subtree.key) {
	    rangeSearch(subtree.left, low, high, ret);
	}
	else if (low > subtree.key) {
	    rangeSearch(subtree.right, low, high, ret);
	}
	else {
	    ret.add(subtree.data);
	    rangeSearch(subtree.left, low, high, ret);
	    rangeSearch(subtree.right, low, high, ret);
	}
    }


    /**
     * @return the largest key in the tree; 0 if the key is empty
     */
    public int maxKey() {
	if (root == null) {
	    return 0;
	}
	TreeNode cur = root;
	while (cur.right != null) {
	    cur = cur.right;
	}
	return cur.key;
    }

}
