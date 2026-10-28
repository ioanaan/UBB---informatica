public class AudiCar extends Car {
    private String market;

    public AudiCar(int year, double price) {
        super(year, price);
    }

    @Override
    public String toString(){
        return super.toString() + market;
    }
}