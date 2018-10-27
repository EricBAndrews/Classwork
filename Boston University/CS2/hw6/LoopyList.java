package hw6;


public class LoopyList {
    public class Node {
	int value;
	Node next = null;
	Node (int value) {
	    this.value = value;
	}
    }
	
    public Node head = null;
    /*
     * If loopLength <=0, there will be no loop, just head of length prefix
     */
    public LoopyList(int prefixLength, int loopLength) {
	// Build a prefix one longer than requested and then
	// delete the first node -- makes life easier,
	// because you don't have to handle prefixLength = 0
	// as a special case
		
	// DO NOT MODIFY THIS METHOD
	head = new Node(0);
	Node last = head;
	for (int i = 1;i<=prefixLength; i++) {
	    last.next = new Node(i);
	    last = last.next;
	}
	if (loopLength > 0) {
	    Node lastPrefixNode = last;
	    for (int i = 1; i<=loopLength; i++) {
		last.next = new Node(prefixLength+i);
		last = last.next;
	    }
	    last.next = lastPrefixNode.next;
	}
	head = head.next;
    }
	
    /**
     * @return whether the list terminates with a null or points back to itself
     */
    public boolean isLoopy () {
	Node fastPoint = head;
	Node slowPoint = head;
	if ((slowPoint == null) || (slowPoint.next == null)) { // case of empty, single-item list
	    return false;
	}
	do { // do while so that it doesn't immediately break
	    for (int i = 0; i < 2; i++) {
		if (fastPoint.next == null) {
		    return false;
		}
		else {
		    fastPoint = fastPoint.next;
		}
	    }
	    slowPoint = slowPoint.next;
	} while (slowPoint != fastPoint);
	return true;
    }
	
	
    /**
     * changes a loopy list to a straight one; does not modify if not loopy
     * @return whether the list was loopy and thus modified
     */
    public boolean straighten () {
	// make sure list is loopy and initialize pointers to within the loop
	Node fastPoint = head;
	Node slowPoint = head;
	if ((slowPoint == null) || (slowPoint.next == null)) { // case of empty, single-item list
	    return false;
	}
	do {
	    for (int i = 0; i < 2; i++) {
		if (fastPoint.next == null) {
		    return false;
		}
		else {
		    fastPoint = fastPoint.next;
		}
	    }
	    slowPoint = slowPoint.next;
	} while (slowPoint != fastPoint);
	// fully looped list (last node linked to head)
	if (fastPoint == head) {
	    while (fastPoint.next != head) {
		fastPoint = fastPoint.next;
	    }
	    fastPoint.next = null;
	    return true;
	}
	// straighten
	Node tempHead = head;
	while (fastPoint.next != tempHead.next) {
	    fastPoint = fastPoint.next;
	    tempHead = tempHead.next;
	}
	fastPoint.next = null;
	return true;
    }
	
    public String toString() {
	// DO NOT MODIFY THIS METHOD
	if (head == null) return "[]";
	String s = "[";
	Node p;
	for (p = head; p.next!=null; p=p.next) {
	    s+=p.value+", ";
	    if (s.length()>1000) {
		return "String is getting too long; perhaps your list is loopy";
	    }
	}
	s+=p.value+"]"; // last one is special, because it has no comma after
	return s;
    }

}
