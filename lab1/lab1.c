#include <stdio.h>
#include <math.h>

int main() {
    double a = 1.0;
    double b = -5.0;
    double c = 6.0;
    double d, x1, x2;
    d = pow(b, 2) - 4 * a * c;
    x1 = (-b + pow(d, 0.5)) / (2 * a);
    x2 = (-b - pow(d, 0.5)) / (2 * a);
    
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    return 0;
}
