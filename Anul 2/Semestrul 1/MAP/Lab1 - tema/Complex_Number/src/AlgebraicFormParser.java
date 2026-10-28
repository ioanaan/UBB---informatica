public class AlgebraicFormParser implements ComplexNumberParser {

    @Override
    public ComplexNumber parse(String text) throws InvalidExpressionException {
        int p = Math.max(text.lastIndexOf('+'), text.lastIndexOf('-'));

        String realText;
        String imagText;

        if (p > 0) {
            realText = text.substring(0, p);
            imagText = text.substring(p);
        }
        else if (text.endsWith("i")) {
            realText = "0";
            imagText = text;
        }
        else {
            realText = text;
            imagText = null;
        }

        double real = toNumber(realText);
        double imag = (imagText == null) ? 0.0 : imaginaryCoefficient(imagText);
        return new ComplexNumber(real, imag);

    }

    private double imaginaryCoefficient(String t) throws InvalidExpressionException {

        if (!t.endsWith("i")) {
            throw new InvalidExpressionException(t);
        }

        String c = t.substring(0, t.length() - 1);
        if (c.endsWith("*")) {
            c = c.substring(0, c.length() - 1);
        }

        if (c.isEmpty() || c.equals("+")) return 1;
        if (c.equals("-")) return -1;

        return toNumber(c);
    }

    private double toNumber(String t) throws InvalidExpressionException {

        try{
            return Double.parseDouble(t);
        }catch (NumberFormatException e){
            throw new InvalidExpressionException("Invalid number: " + t);
        }
    }
}
