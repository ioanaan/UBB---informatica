public class Car {
    private int year;
    private double price;

    public Car(int year, double price)
    {
        this.year = year;
        this.price = price;
    }

    public int getYear()
    {
        return year;
    }

    public double getPrice()
    {
        return price;
    }

    public String toString()
    {
        return "price: " + price + "year: " + year;
    }
}

/*public class AudiCar extends Car {
    private String market;

    public AudiCar(int year, double price) {
        super(year, price);
    }

    @Override
    public String toString(){
        return super.toString() + market;
    }
}

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
*/