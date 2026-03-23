#include <stdio.h>
#include <locale.h>
#include "triangle.h"

int main() {
    double a, b, c;

    printf("three sides of the triangle (with spaces): ");
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("ERROR!\n");
        return 1;
    }

    if (a + b > c && a + c > b && b + c > a) {
        double p = get_perimeter(a, b, c);
        double s = get_area(a, b, c);
        
        printf("perimeter: %.2lf\n", p);
        printf("ploshad: %.2lf\n", s);
    } else {
        printf("ERROR: this triangle does not exist!\n");
    }

    return 0;
}
