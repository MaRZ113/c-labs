#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main() {
    int n;
    char op;
    printf("razmernost' n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR: incorrect razmernost'!\n");
        return 1;
    }

    double** A = allocate_matrix(n);
    double** B = allocate_matrix(n);

    printf("elements of first matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("elements of second matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }

    printf("operation to use? (+, -, *): ");
    scanf(" %c", &op); 

    double** C = calculate(A, B, n, op);

    printf("result:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", C[i][j]);
        }
        printf("\n");
    }

    free_matrix(C, n);
    free_matrix(A, n);
    free_matrix(B, n);

    return 0;
}
