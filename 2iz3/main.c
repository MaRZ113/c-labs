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

void swap_pairs(int **mat, int n) {
    int i, r1, c1, r2, c2, temp;
    int total = n * n;
    for (i = 0; i < total - 1; i += 2) {
        r1 = i / n;
        c1 = i % n;
        r2 = (i + 1) / n;
        c2 = (i + 1) % n;
        
        temp = mat[r1][c1];
        mat[r1][c1] = mat[r2][c2];
        mat[r2][c2] = temp;
    }
}

int has_identical_lines(int **mat, int n) {
    int i, j, ok;
    for (i = 0; i < n; i++) {
        ok = 1;
        for (j = 1; j < n; j++) {
            if (mat[i][j] != mat[i][0]) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    
    for (j = 0; j < n; j++) {
        ok = 1;
        for (i = 1; i < n; i++) {
            if (mat[i][j] != mat[0][j]) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    return 0;
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
    int min_val, min_idx, odd_count;
    int cur_idx;
    int same_a, same_b;
    FILE *f;
    clock_t start_time, end_time;
    double work_time;

    start_time = clock();
    srand((unsigned int)time(NULL));

    printf("Enter matrix size N: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    a = create_matrix(n);
    b = create_matrix(n);

    f = fopen("input.txt", "w");
    if (!f) return 1;
    fprintf(f, "%d\n", n);
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
    a = NULL;
    b = NULL;

    f = fopen("input.txt", "r");
    if (!f) return 1;
    fscanf(f, "%d", &n);
    
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

    fprintf(f, "addition (A + B):\n");
    print_matrix(f, sum, n);
    
    fprintf(f, "\nmultip (A * B):\n");
    print_matrix(f, prod, n);

    min_val = a[0][0];
    min_idx = 1;
    odd_count = 0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cur_idx = i * n + j + 1;
            if (a[i][j] < min_val) {
                min_val = a[i][j];
                min_idx = cur_idx;
            }
            if (a[i][j] % 2 != 0) {
                odd_count++;
            }
        }
    }
    
    fprintf(f, "\nmatrix A stats before swap:\n");
    fprintf(f, "min element index: %d (Value: %d)\n", min_idx, min_val);
    fprintf(f, "odd numbers count: %d\n", odd_count);

    fprintf(f, "\nmatrix A after swapping pairs:\n");
    print_matrix(f, a, n);

    same_a = has_identical_lines(a, n);
    same_b = has_identical_lines(b, n);
    swap_pairs(a, n);
    
    fprintf(f, "\nidentical lines check:\n");
    fprintf(f, "matrix A: %s\n", same_a ? "yes" : "no");
    fprintf(f, "matrix B: %s\n", same_b ? "yes" : "no");

    fclose(f);

    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(sum, n);
    free_matrix(prod, n);

    end_time = clock();
    work_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("results to output.txt\n");
    printf("execution time: %.3f seconds\n", work_time);

    return 0;
}
