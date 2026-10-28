public class Expression {

    private ComplexNumber[] operands;
    private Operation operation;

    public Expression(ComplexNumber[] operands, Operation operation) {
        this.operands = new ComplexNumber[operands.length];
        for (int i = 0; i < operands.length; i++) {
            this.operands[i] = operands[i];
        }
        this.operation = operation;
    }

    public ComplexNumber evaluate() {
        ComplexNumber result = operands[0];
        for (int i = 1; i < operands.length; i++) {
            result = operation.apply(result, operands[i]);
        }
        return result;
    }
}
