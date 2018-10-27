package hw5;

/*
 * RPN calculator supporting addition, subtraction and multiplication
 * of anything that implements the CalculatorOperand interface
 */

public class RPNCalculator<T extends CalculatorOperand<T>> {

    ListStack<T> stack; // The stack holding the operands
    
    static public enum OperationType {ADD, SUBTRACT, MULTIPLY};

    public RPNCalculator () { // Constructor
	stack = new ListStack<T>();
    }

    public void operand (T value) { // Push operand to stack
	stack.push(value);
    }
    /*
     * Performs an operation on the two topmost elements of the stack
     * If t2 is topmost and t1 is second topmost, then t1 and t2 will be removed
     * from the stack and (t1 op t2) will be placed on top of the stack.
     * Does not modify the stack if it contains fewer than two elements.
     */
    public void operation (OperationType operation) {
	if (stack.hasTwoOperands()) {
	    T op2 = stack.pop();
	    T op1 = stack.pop();
	    T ret = null;
	    switch (operation) {
	    case ADD:
		ret = op1.add(op2);
		break;
	    case SUBTRACT:
		ret = op1.subtract(op2);
		break;
	    case MULTIPLY:
		ret = op1.multiply(op2);
		break;
	    }
	    stack.push(ret);
	    return;
	}
	return;
    }
    /*
     * Prints the calculator stack
     */
    public String toString() {
	if (stack.isEmpty()) {
	    return "Empty stack\n";
	}
	else {
	    return stack.toString();
	}
    }
}


