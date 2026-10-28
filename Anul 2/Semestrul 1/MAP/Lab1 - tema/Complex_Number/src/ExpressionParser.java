public interface ExpressionParser {

    Expression parse(String[] args) throws InvalidExpressionException;
}
