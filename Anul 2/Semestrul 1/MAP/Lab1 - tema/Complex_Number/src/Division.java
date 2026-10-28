public class Division implements Operation {

    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double denominator = b.getReal() * b.getReal() + b.getImaginary() * b.getImaginary();
        if (denominator == 0) {
            throw new ArithmeticException("Division by zero");
        }
        double re = (a.getReal() * b.getReal() + a.getImaginary() * b.getImaginary()) / denominator;
        double im = (a.getImaginary() * b.getReal() - a.getReal() * b.getImaginary()) / denominator;
        return new ComplexNumber(re, im);
    }
}