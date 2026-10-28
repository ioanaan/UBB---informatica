//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        OperationFactory factory = OperationFactory.getInstance();

        ComplexNumberParser numberParser = new AlgebraicFormParser();
        ExpressionParser parser = new CommandLineExpressionParser(numberParser, factory);

        try {
            Expression expression = parser.parse(args);
            ComplexNumber result = expression.evaluate();
            System.out.println(result);
        } catch (InvalidExpressionException e) {
            System.out.println("Invalid expression: " + e.getMessage());
        } catch (ArithmeticException e) {
            System.out.println("Solving error: " + e.getMessage());
        }
    }
}