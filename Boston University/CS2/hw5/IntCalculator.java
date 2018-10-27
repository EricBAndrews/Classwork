package hw5;

/*
 * driver for the RPN calculator on arbitrary-length integers; see comments below 
 */

import java.util.Scanner;

public class IntCalculator {
    /*
     * Drives the RPN (postfix) calculator for arbitrary-length integers.  The user can enter
     * a decimal integer, which gets passed to the calculator as an operand,
     * the operations "+", "-" and "*", which also get passed to the calculator, or
     * "q", which quits the calculator
     */
    public static void main (String [] args) {
	Scanner scan = new Scanner (System.in);
	RPNCalculator<IntegerOperand> calc = new RPNCalculator<IntegerOperand> ();

	while (true) {
	    boolean printStack = true;
	    if (scan.hasNextBigInteger()) // If the next input is an operand
		calc.operand(new IntegerOperand(scan.nextBigInteger()));
	    else {
		String s = scan.next();		
		// The three operators
		if (s.equals("+")) {
		    calc.operation(RPNCalculator.OperationType.ADD);
		} else if (s.equals("-")) {
		    calc.operation(RPNCalculator.OperationType.SUBTRACT);
		} else if (s.equals("*")) {
		    calc.operation(RPNCalculator.OperationType.MULTIPLY);
		} else if (s.equals("q")) { // Quit
		    scan.close();
		    return;
		} else { // Inform the user of proper input format
		    System.out.println("Valid inputs are integers; operands +, -, *; and q to quit.");
		    printStack = false;
		}
	    }
	    if (printStack) System.out.print(calc);
	}
    }
}
