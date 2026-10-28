public class Addition implements Operation {

    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double re = a.getReal() + b.getReal();
        double im = a.getImaginary() + b.getImaginary();
        return new ComplexNumber(re, im);
    }
}
