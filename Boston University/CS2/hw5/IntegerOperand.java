package hw5;

import java.math.BigInteger;

public class IntegerOperand implements CalculatorOperand<IntegerOperand> {

    BigInteger value;

    IntegerOperand (BigInteger value) {
	this.value = value;
    }
	
    public IntegerOperand add (IntegerOperand that) {
	return new IntegerOperand(this.value.add(that.value));
    }
    public IntegerOperand subtract (IntegerOperand that) {
	return new IntegerOperand(this.value.subtract(that.value));
    }
    public IntegerOperand multiply (IntegerOperand that) {
	return new IntegerOperand(this.value.multiply(that.value));
    }
	
    public String toString () {
	return value.toString();
    }	
}

