#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matrix.h"

int main() {
    int n;
    char op;
    int i, j;
    double** A;
    double** B;
    double** C;

    printf("razmernost' n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR: ne ta razmernost'!\n");
        return 1;
    }

    A = allocate_matrix(n);
    B = allocate_matrix(n);

    printf("elements of first matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("elements of second matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }

    printf("operation to use (+, -, *): ");
    scanf(" %c", &op); 

    C = calculate(A, B, n, op);

    printf("result:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.2lf ", C[i][j]);
        }
        printf("\n");
    }

    free_matrix(C, n);
    free_matrix(A, n);
    free_matrix(B, n);

    return 0;
}
