public class Multiplication implements  Operation {

    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double re =  a.getReal() * b.getReal() - a.getImaginary() * b.getImaginary();
        double im = a.getReal() * b.getImaginary() + a.getImaginary() * b.getReal();
        return new ComplexNumber(re, im);
    }
}
