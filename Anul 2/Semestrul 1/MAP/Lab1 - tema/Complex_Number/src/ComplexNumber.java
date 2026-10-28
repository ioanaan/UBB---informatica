public class ComplexNumber {

    private double real;
    private double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }
    public double getImaginary() {
        return imaginary;
    }

    @Override
    public String toString() {
        double re = Math.round(real * 100) / 100.0;
        double im = Math.round(Math.abs(imaginary) * 100) / 100.0;

        String reText = (re == (long) re) ? String.valueOf((long) re) : String.valueOf(re);
        String imText = (im == (long) im) ? String.valueOf((long) im) : String.valueOf(im);

        if (im == 0) {
            return reText;
        }
        String sign = (imaginary < 0) ? " - " : " + ";
        String imaginaryPart = (im == 1) ? "i" : imText + "*i";
        return reText + sign + imaginaryPart;
    }
}
