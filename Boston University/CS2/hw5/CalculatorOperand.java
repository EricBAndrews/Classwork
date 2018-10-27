package hw5;

public interface CalculatorOperand<T> {
    public T add(T that);
    public T subtract(T that);
    public T multiply(T that);
}
