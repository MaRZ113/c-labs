#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int n) {
    int i, j;
    int **mat = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            mat[i][j] = rand() % 10;
        }
    }
    return mat;
}

void free_matrix(int **mat, int n) {
    int i;
    if (!mat) return;
    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

void add_matrices(int **a, int **b, int **res, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
}

void mult_matrices(int **a, int **b, int **res, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = 0;
            for (k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void print_matrix(FILE *f, int **mat, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(f, "%4d", mat[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main(void) {
    int n, i, j;
    int **a = NULL, **b = NULL, **sum = NULL, **prod = NULL;
    FILE *f;
    clock_t start_time, end_time;
    double work_time;

    start_time = clock();
    srand((unsigned int)time(NULL));

    printf("enter matrix size N: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    a = create_matrix(n);
    b = create_matrix(n);

    f = fopen("input.txt", "w");
    if (!f) return 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) fprintf(f, "%d ", a[i][j]);
        fprintf(f, "\n");
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) fprintf(f, "%d ", b[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);

    free_matrix(a, n);
    free_matrix(b, n);

    f = fopen("input.txt", "r");
    if (!f) return 1;
    
    a = (int**)malloc(n * sizeof(int*));
    b = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) fscanf(f, "%d", &a[i][j]);
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) fscanf(f, "%d", &b[i][j]);
    }
    fclose(f);

    sum = create_matrix(n);
    prod = create_matrix(n);

    add_matrices(a, b, sum, n);
    mult_matrices(a, b, prod, n);

    f = fopen("output.txt", "w");
    if (!f) return 1;
    
    fprintf(f, "matrix A + B:\n");
    print_matrix(f, sum, n);
    fprintf(f, "\nmatrix A * B:\n");
    print_matrix(f, prod, n);
    fclose(f);

    end_time = clock();
    work_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("results in output.txt\n");
    printf("time: %.3f seconds\n", work_time);
    
    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(sum, n);
    free_matrix(prod, n);

    return 0;
}
