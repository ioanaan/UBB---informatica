package ex.functional;

import java.util.ArrayList;
import java.util.List;

public class AreaDemo {

    public static <E> void printArea(List<E> figures, Area<E> area) {
        for (E figure : figures) {
            System.out.println(area.compute(figure));
        }
    }

    public static void main(String[] args) {
        List<Circle> circles = List.of(new Circle(2),
                new Circle(3), new Circle(4));

        Area<Circle> anonymousArea = new Area<Circle>() {
            @Override
            public double compute(Circle figure) {
                return Math.PI * figure.getRadius() * figure.getRadius();
            }
        };

        System.out.println("Anonymous Area ");
        printArea(circles, anonymousArea);

        /// lambda
        Area<Circle> lambdaArea = c->Math.PI * Math.pow(c.getRadius(), 2);
        System.out.println("lambdaArea ");
        printArea(circles, lambdaArea);

        /// referinta
        Area<Circle> referenceArea = Circle::area;
        System.out.println("ReferenceArea ");
        printArea(circles, referenceArea);

        System.out.println();
        List<Square> squares = List.of(new Square(4), new Square(3));
        printArea(squares, s->s.getSide()*s.getSide());
    }
}
