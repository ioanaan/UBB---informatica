public class PorscheCar extends Car {
    private String model;
    @Override
    public String toString(){
        return super.toString() + model;
    }

    public PorscheCar(int year, double price, String model)
    {
        super(year, price);
        this.model = model;
    }
}