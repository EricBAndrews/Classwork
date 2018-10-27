package hw5;

import java.util.Scanner;
/**
 * driver for the RPN calculator on polynomials; see comments below 
 * @author Leo Reyzin
 *
 */
public class PolynomialCalculator {
    /**
     * Drives the RPN (postfix) calculator for polynomials with integer coefficients. 
     * The user can enter a monomial as two space-separate decimal integers
     * coefficient and degree (degree must be nonnegative), 
     * which gets passed to the calculator as an operand,
     * the operations "+", "-" and "*", which also get passed to the calculator,
     * or "q", which quits the calculator
     * 
     * Direct entry of polynomials other than monomials is not supported; however,
     * it is easy to enter the monomials and then add them up using the appropriate
     * number of "+" operations, thus getting the desired polynomial 
     * 
     * @param args ignored
     */
	
    public static void main (String [] args) {
	Scanner scan = new Scanner (System.in);
	RPNCalculator<Polynomial> calc = new RPNCalculator<Polynomial>();

	while(true) {
	    boolean printStack = true;
	    if (scan.hasNextInt()) { // If the next input is an operand
		int coeff = scan.nextInt();  // the first integer is the coefficient
		int degree;

		while(true) { // keep trying to get the second integer, the degree
		    if (!scan.hasNextInt()) // next input token is not an integer
			scan.next(); // ignore the next input token because it is not an integer
		    else { // it's an integer
			degree = scan.nextInt();
			if (degree >= 0) // make sure it's nonnegative
			    break;
		    }
		    System.out.print("Please enter the nonnegative integer degree of the monomial with coefficient "+coeff+": ");
		}
		calc.operand(new Polynomial(coeff, degree));
	    } else {
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
		    printStack = false;
		    System.out.println("Valid inputs are monomials (as space-separated integer coefficient and degree); operations +, -, *; and q to quit.");
		}
	    }
	    if (printStack) System.out.print(calc);
	}
    }
}
