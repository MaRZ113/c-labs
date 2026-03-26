#ifndef MATRIX_H
#define MATRIX_H

double** allocate_matrix(int n);
void free_matrix(double** mat, int n);
double** calculate(double** A, double** B, int n, char op);

#endif
