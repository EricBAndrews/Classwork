package hw6;
import java.util.LinkedList;
import java.util.ListIterator;
 
public class DirectoryTree {
    // TODO nothing here is implemented, these are just empty
    // shells so the compiler doesn't complain
    // Implement private members, public methods,
    // and private helper methods, etc., as needed,
    // in order to get the behavior described on the pset
    // You will want to maintain two private members:
    // the root and the current directory.
    
    private class Dir {
	String name;
	String path; // makes pwd easy
	Dir parent; // parent directory; root has this as null. makes cdUp easy.
	LinkedList<Dir> subDirs = new LinkedList<Dir>();
	Dir(Dir par, String n, String path) {
	    this.parent = par;
	    this.name = n;
	    if (path.compareTo("/") == 0) {
		this.path = path + name;
	    }
	    else {
		this.path = path + "/" + name;
	    }
	}
    }

    Dir root = new Dir(null, "", "");
    Dir curDir = root;

    public boolean mkdir(String name) {
	for (Dir toCheck : curDir.subDirs) {
	    if (toCheck.name.equals(name)) {
		return false;
	    }
	}
	curDir.subDirs.add(new Dir(curDir, name, curDir.path));
	return true;
    }

    public boolean rmdir(String name) {
	for (Dir toCheck : curDir.subDirs) {
	    if (toCheck.name.equals(name)) {
		curDir.subDirs.remove(toCheck);
		return true;
	    }
	}
	return false;
    }

    public String ls() {
	String ret = "";
	for (Dir toList : curDir.subDirs) {
	    ret += toList.name;
	    ret += " ";
	}
	if (!ret.equals("")) {
	    ret += "\n";
	}
	return ret;
    }
	
    public boolean cd (String name) {
	for (Dir toCheck : curDir.subDirs) {
	    if (toCheck.name.equals(name)) {
		curDir = toCheck;
		return true;
	    }
	}
	return false;
    }
	
    public boolean cdUp() {
	if (curDir.parent != null) {
	    curDir = curDir.parent;
	    return true;
	}
	return false;
    }
	
    public String printSubTree() {
	return treeHelper(curDir, 0);
    }

    public String treeHelper(Dir toList, int depth) {
	String ret = "";
	for (int i = 0; i < depth - 1; i++) {
	    ret += "  ";
	}
	if (depth != 0) {
	    ret += toList.name + "\n";
	}
	for (Dir dirIter : toList.subDirs) {
	    ret += treeHelper(dirIter, depth + 1);
	}
	return ret;
    }
	
    public String pwd () {
	return curDir.path;
    }
	
    public int numNodes() {
	return sizeHelper(curDir);
    }

    public int sizeHelper(Dir toList) {
	int ret = 1;
	for (Dir toCount : toList.subDirs) {
	    ret += sizeHelper(toCount);
	}
	return ret;
    }
}
