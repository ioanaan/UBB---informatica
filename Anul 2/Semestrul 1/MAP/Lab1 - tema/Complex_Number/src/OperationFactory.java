public class OperationFactory {

    private static OperationFactory instance;

    private OperationFactory() {
    }

    public static OperationFactory getInstance() {
        if (instance == null) {
            instance = new OperationFactory();
        }
        return instance;
    }

    public Operation create(String symbol) throws InvalidExpressionException {
        switch (symbol) {
            case "+":
                return new Addition();
            case "-":
                return new Subtraction();
            case "*":
                return new Multiplication();
            case "/":
                return new Division();
            default:
                throw new InvalidExpressionException("Invalid symbol");
        }
    }
}
