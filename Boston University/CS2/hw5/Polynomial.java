package hw5;

/**
 * Polynomial Class which implements the CalculatorOperand interface. 
 * Maintains polynomials as an ordered linked list, with monomials arranged by decreasing degree
 */
public class Polynomial implements CalculatorOperand<Polynomial> {

    private class PolyNode {
	int coeff;
	int degree;
	PolyNode next;
	PolyNode(int c, int d) {
	    this.coeff = c;
	    this.degree = d;
	    this.next = null;
	}
    }

    private PolyNode monomialsList = new PolyNode(0, 0);

    Polynomial(int coeff, int degree) {
	if ((coeff != 0) && (degree >= 0)) {
	    monomialsList.next = new PolyNode(coeff, degree);
	}
    }

    /**
     * Returns this + coeff*x^degree * that; does not modify this or that. 
     * Assumes coeff is nonzero.
     */
    public Polynomial addTimesMonomial (Polynomial that, int coeff, int degree) {
	// declarations
	Polynomial ret = new Polynomial(0, 0);
	Polynomial mulRet = new Polynomial(0, 0);
	PolyNode thisCur = this.monomialsList.next;
	PolyNode thatCur = that.monomialsList.next;
	PolyNode retCur = mulRet.monomialsList;
	PolyNode toAdd;
	// mulRet = that * coeff*x^degree
	while (thatCur != null) {
	    retCur.next = new PolyNode(thatCur.coeff * coeff, thatCur.degree + degree);
	    thatCur = thatCur.next;
	    retCur = retCur.next;
	}
	// this + mulRet
	retCur = ret.monomialsList;
	thatCur = mulRet.monomialsList.next; // that = that * coeff*x^degree w/o changing that
	while (thisCur != null && thatCur != null) {
	    if (thisCur.degree == thatCur.degree) {
		toAdd = new PolyNode(thisCur.coeff + thatCur.coeff, thisCur.degree);
		thisCur = thisCur.next;
		thatCur = thatCur.next;
	    }
	    else if (thisCur.degree > thatCur.degree) {
		toAdd = new PolyNode(thisCur.coeff, thisCur.degree);
		thisCur = thisCur.next;
	    }
	    else {
		toAdd = new PolyNode(thatCur.coeff, thatCur.degree);
		thatCur = thatCur.next;
	    }
	    if (toAdd.coeff != 0) { 
		retCur.next = toAdd;
		retCur = retCur.next;
	    }
	    else { // deal with 0x^y
	    	retCur.next = null;
	    }
	}
	// glue on the rest
	if (thatCur == null) {
	    while (thisCur != null) {
		toAdd = new PolyNode(thisCur.coeff, thisCur.degree);
		thisCur = thisCur.next;
		retCur.next = toAdd;
		retCur = retCur.next;
	    }
	}
	else if (thisCur == null) {
	    while (thatCur != null) {
		toAdd = new PolyNode(thatCur.coeff, thatCur.degree);
		thatCur = thatCur.next;
		retCur.next = toAdd;
		retCur = retCur.next;
	    }
	}
	return ret;
    }

    /**
     * Returns this + that; does not modify this or that
     */
    public Polynomial add (Polynomial that) {
	return this.addTimesMonomial(that, 1, 0);
    }

    /**
     * Returns this-that; does not modify this or that
     */
    public Polynomial subtract (Polynomial that) {
	return this.addTimesMonomial(that, -1, 0);
    }

    /**
     * Returns this*that; does not modify this or that
     */
    public Polynomial multiply (Polynomial that) {
	Polynomial ret = new Polynomial(0, 0);
	PolyNode thisCur = this.monomialsList.next;
	while (thisCur != null) {
	    ret = ret.addTimesMonomial(that, thisCur.coeff, thisCur.degree);
	    thisCur = thisCur.next;
	}
	return ret;
    }

    /**
     * Prints the polynomial the way a human would like to read it
     * @return the human-readable string representation 
     */
    public String toString () {
	if (monomialsList.next == null)
	    return "0";

	String ret = monomialsList.next.coeff<0 ? "-" : "";
	for (PolyNode p = monomialsList.next; p!=null; p=p.next) {
	    if (p.degree == 0 || (p.coeff!=1 && p.coeff!=-1))
		ret = ret + java.lang.Math.abs(p.coeff) ;
	    if (p.degree > 0)
		ret = ret + "x";
	    if (p.degree > 1)
		ret = ret + "^" + p.degree;
	    if (p.next != null)
		ret = ret + (p.next.coeff<0 ? " - " : " + ");
	}
	return ret;
    }	
}
