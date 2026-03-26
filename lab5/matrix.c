#include <stdlib.h>
#include "matrix.h"

double** allocate_matrix(int n) {
    int i;
    double** mat = (double**)malloc(n * sizeof(double*));
    for (i = 0; i < n; i++) {
        mat[i] = (double*)malloc(n * sizeof(double));
    }
    return mat;
}

void free_matrix(double** mat, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

double** calculate(double** A, double** B, int n, char op) {
    int i, j, k;
    double** C = allocate_matrix(n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (op == '+') {
                C[i][j] = A[i][j] + B[i][j];
            } else if (op == '-') {
                C[i][j] = A[i][j] - B[i][j];
            } else if (op == '*') {
                C[i][j] = 0;
                for (k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    return C;
}
