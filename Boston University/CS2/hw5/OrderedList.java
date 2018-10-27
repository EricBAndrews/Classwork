package hw5;

/*
 * Generic ordered list for use with any comparable type
 */

public class OrderedList <T extends Comparable<T>>{
    private class Node {
	T value;
	Node next;
	Node(T v, Node n) {
	    value = v;
	    next = n;
	}
    }
    
    private Node head = new Node(null, null);
    
    public void insert (T v) {
	Node ins = new Node(v, null); // to be inserted
	if (head.next == null) { // empty list
	    head.next = ins;
	    return;
	}
	Node prev = head, next = head.next;
	if (v.compareTo(next.value) < 0) { // v less than first value in the list
	    ins.next = next;
	    prev.next = ins;
	    return;
	}
	while (next != null) { // iterate through list
	    if (next.value.compareTo(ins.value) > 0) { // once next > ins, insert
		prev.next = ins;
		ins.next = next;
		return;
	    }
	    prev = next;
	    next = next.next;
	}
	prev.next = ins; // v greater than everything in list
	return;
    }

    public boolean delete (T v) {
	Node prev = head, cur = head.next;
	while (cur != null) {
	    int compResult = cur.value.compareTo(v);
	    if (compResult == 0) {
		prev.next = cur.next;
		return true;
	    }
	    if (compResult > 0) {
		return false;
	    }
	    prev = cur;
	    cur = cur.next;
	}
	return false;
    }
	
    public boolean contains (T v) {
	Node cur = head.next;
	while (cur != null) {
	    if (cur.value.compareTo(v) == 0) {
		return true;
	    }
	    cur = cur.next;
	}
	return false;
    }
    
    OrderedList<T> merge (OrderedList<T> that) {
	OrderedList<T> ret = new OrderedList<T>();
	Node retCur = ret.head;
	Node thisCur = this.head.next;
	Node thatCur = that.head.next;
	while ((thisCur != null) && (thatCur != null)) {
	    // I know those aren't necessary parentheses but I find it makes things more legible
	    Node toAdd = new Node(null, null); // node to be put on the end of the list
	    if (thisCur.value.compareTo(thatCur.value) > 0) {
		toAdd.value = thatCur.value;
		thatCur = thatCur.next;
	    }
	    else {
		toAdd.value = thisCur.value;
		thisCur = thisCur.next;
	    }
	    retCur.next = toAdd;
	    retCur = retCur.next;
	}
	if (thisCur == null) { // only that remaining
	    while (thatCur != null) {
		retCur.next = new Node(thatCur.value, null);
		retCur = retCur.next;
		thatCur = thatCur.next;
	    }
	}
	else { // only this remaining
	    while (thisCur != null) {
		retCur.next = new Node(thisCur.value, null);
		retCur = retCur.next;
		thisCur = thisCur.next;
	    }
	}
	return ret;
    }
    
    public String toString() {
	if (head.next == null) return "[]";
	String s = "[";
	Node p;
	for(p = head.next; p.next != null; p = p.next) {
	    s += p.value + ", ";
	}
	s += p.value + "]"; // last one is special, because it has no comma after
	return s;
    }

}
