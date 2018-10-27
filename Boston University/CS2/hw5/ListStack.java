package hw5;

/*
 * Generic stack
 */

public class ListStack<T> {
    private class Node {
	T item;
	Node next;
	Node (T item, Node next) {
	    this.item = item;
	    this.next = next;
	}
    }

    private Node head = null;
	
    public void push (T item) {
	head = new Node(item, head);
    }
	
    public T pop () {
	if (isEmpty()) {
	    throw new RuntimeException ("Stack Underflow");
	}
	T ret = head.item;
	head = head.next;
	return ret;
    }
	
    public boolean isEmpty() {
	return head == null;
    }

    public boolean hasTwoOperands() {
	if (head == null) {
	    return false;
	}
	return head.next != null;
    }

    public String toString () {
	String s = "";
	for (Node p = head; p != null; p = p.next) {
	    s = p.item.toString() + "\n" + s;
	}
	return s;
    }
}
