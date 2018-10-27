package hw5;

public class OrderedListDriver {

    public static void main(String[] args) {
	OrderedList<Integer> l = new OrderedList<Integer>();
	// insert some stuff
	l.insert(3);
	l.insert(2);
	l.insert(12);
	System.out.println(l);
	// [2, 3, 12]
	// create a new list, add stuff and delete one real and a dummy
	OrderedList<Integer> m = new OrderedList<Integer>();
	m.insert(17);
	m.insert(9);
	m.insert(12);
	m.insert(4);
	m.delete(9);
	m.delete(2);
	// test prints
	System.out.println(m);
	// [4, 12, 17]
	System.out.println(m.contains(17)); // true
	System.out.println(m.contains(30)); // false
	// merge
	OrderedList<Integer> lm = new OrderedList<Integer>();
	lm = l.merge(m);
	System.out.println(lm);
	// [2, 3, 4, 12, 12, 17]
    }
}
