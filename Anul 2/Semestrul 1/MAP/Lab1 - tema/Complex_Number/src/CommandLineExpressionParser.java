public class CommandLineExpressionParser implements ExpressionParser {

    private ComplexNumberParser numberParser;
    private OperationFactory operationFactory;

    public CommandLineExpressionParser(ComplexNumberParser numberParser, OperationFactory operationFactory) {
        this.numberParser = numberParser;
        this.operationFactory = operationFactory;
    }

    @Override
    public Expression parse(String[] args) throws InvalidExpressionException {

        checkStructure(args);
        ComplexNumber[] operands = parseOperands(args);
        Operation operation = operationFactory.create(args[1]);
        return new Expression(operands, operation);

    }

    private void checkStructure(String[] args) throws InvalidExpressionException {

        if (args.length < 3 || args.length % 2 == 0) {
            throw new InvalidExpressionException("Invalid number of arguments");
        }

        String op = args[1];
        for (int i = 3; i < args.length; i += 2) {
            if (!args[i].equals(op)) {
                throw new InvalidExpressionException("Different operators");
            }
        }

    }

    private ComplexNumber[] parseOperands(String[] args) throws InvalidExpressionException {

        ComplexNumber[] operands = new ComplexNumber[(args.length + 1) / 2];
        for (int i = 0; i < args.length; i += 2) {
            operands[i / 2] = numberParser.parse(args[i]);
        }

        return operands;
    }

}
