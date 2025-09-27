#include <stdio.h>
#include <math.h>

int TriangleProperties(double side1, double side2, double side3, double* perimeter, double* area) {
    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
        *perimeter = side1 + side2 + side3;
        double s = (*perimeter) / 2;
        *area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
        return 1; // треугольник существует
    } else {
        return 0; // треугольник не существует
    }
}

int main() {
    double side1, side2, side3;
    printf("Write storony: ");
    scanf("%lf %lf %lf", &side1, &side2, &side3);

    double perimeter, area;
    int result = TriangleProperties(side1, side2, side3, &perimeter, &area);

    if (result) {
        printf("P: %lf\n", perimeter);
        printf("S: %lf\n", area);
    } else {
        printf("not exist.\n");
    }

    return 0;
}
