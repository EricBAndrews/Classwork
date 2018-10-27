
package hw7;

/**
 * Binary search tree, containing items of type String,
 * which allows duplicates by having a counter in each node
 * (rather than inserting duplicate nodes)
 *
 */
public class CountingTree {

    private class TreeNode {
	String key;
	int count; // how many times key appears in the tree
	TreeNode left, right;
	TreeNode(String key) {
	    this.key = key; left = right = null; count = 1;
	}
    }

    private TreeNode root = null;
    private int totalEntries = 0; // total of all counts
    private int distinctEntries = 0; // number of nodes

    /**
     * @return number of total entries (i.e., total of all counts)
     */
    public int getTotalEntries() {return totalEntries;}

    /**
     * @return number of distinct entries (i.e., number of nodes)
     */
    public int getDistinctEntries() {return distinctEntries;}

    /**
     * Inserts key into the tree.  If key is already in,
     * just increments the corresponding counter.  If not,
     * creates a new node.
     * @param key the value to be inserted
     */
    public void insert (String key) {
	root = insertHelper(key, root);
    }

    private TreeNode insertHelper (String key, TreeNode subtree) {
	if (subtree == null) {
	    subtree = new TreeNode(key);
	    distinctEntries++;
	    totalEntries++;
	}
	else {
	    int comp = key.compareTo(subtree.key);
	    if (comp == 0) {
		subtree.count++;
		totalEntries++;
	    }
	    else if (comp < 0) {
		subtree.left = insertHelper(key, subtree.left);
	    }
	    else {
		subtree.right = insertHelper(key, subtree.right);
	    }
	}
	return subtree;
    }

    /**
     * @param key
     * @return number of times key is in the tree, i.e., the count of key 
     * (0 if key not in the tree)
     */
    public int search (String key) {
	TreeNode cur = root;
	int comp = 0;
	do {
	    if (cur == null) {
		return 0;
	    }
	    comp = key.compareTo(cur.key);
	    if (comp < 0) {
		cur = cur.left;
	    }
	    else if (comp > 0) {
		cur = cur.right;
	    }
	} while (comp != 0);
	return cur.count;
    }
    
    /**
     * Creates and returns a new tree, which allows lookup
     * of entries in this tree by their counts.  Thus, in the new
     * tree keys are integers, and data is String.  The new tree has as
     * many nodes as the current tree.  The new tree must allow
     * insertion of nodes with duplicate keys, since counts may repeat.
     * @return the new tree
     */
    public BSTWithDuplicates frequencyTree () {
	BSTWithDuplicates t = new BSTWithDuplicates ();
	frequencyTree(root, t);
	return t;
    }

    /**
     * Private recursive helper for frequencyTree 
     * @param root
     * @param t
     */
    private void frequencyTree (TreeNode root, BSTWithDuplicates t) {
	if (root != null) {
	    // just do a traversal -- any order is fine
	    t.insert(root.count, root.key);
	    frequencyTree(root.left, t);
	    frequencyTree(root.right, t);
	}
    }
}
