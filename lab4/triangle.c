#include <math.h>
#include "triangle.h"

double get_perimeter(double a, double b, double c) {
    return a + b + c;
}

double get_area(double a, double b, double c) {
    double p = get_perimeter(a, b, c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
