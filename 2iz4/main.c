#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n, m, i, j, k, rows;
    int *arr;
    int **mat;
    int *r_sums, *c_sums;
    FILE *fin, *fout;
    clock_t start_time, end_time;
    double work_time;

    start_time = clock();
    srand((unsigned int)time(NULL));

    printf("number of elements N: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;
    
    printf("number of columns M: ");
    if (scanf("%d", &m) != 1 || m < 1) return 1;

    arr = (int*)malloc(n * sizeof(int));
    
    fin = fopen("input.txt", "w");
    if (!fin) return 1;
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
        fprintf(fin, "%d ", arr[i]);
    }
    fclose(fin);

    for (i = 0; i < n; i++) {
        arr[i] = 0;
    }

    fin = fopen("input.txt", "r");
    if (!fin) return 1;
    
    fout = fopen("output.txt", "w");
    if (!fout) {
        fclose(fin);
        return 1;
    }

    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
        if (arr[i] % 35 == 0) {
            fprintf(fout, "PYATSEM ");
        } else if (arr[i] % 5 == 0) {
            fprintf(fout, "PYAT ");
        } else if (arr[i] % 7 == 0) {
            fprintf(fout, "SEM ");
        } else {
            fprintf(fout, "%d ", arr[i]);
        }
    }
    fclose(fin);
    fclose(fout);

    rows = n / m;
    
    if (rows > 0) {
        mat = (int**)malloc(rows * sizeof(int*));
        r_sums = (int*)malloc(rows * sizeof(int));
        c_sums = (int*)malloc(m * sizeof(int));
        
        for (i = 0; i < rows; i++) r_sums[i] = 0;
        for (j = 0; j < m; j++) c_sums[j] = 0;

        printf("\ngenerated matrix %dx%d:\n", rows, m);
        k = 0;
        for (i = 0; i < rows; i++) {
            mat[i] = (int*)malloc(m * sizeof(int));
            for (j = 0; j < m; j++) {
                mat[i][j] = arr[k];
                k++;
                r_sums[i] += mat[i][j];
                c_sums[j] += mat[i][j];
                printf("%4d", mat[i][j]);
            }
            printf(" | sum: %d\n", r_sums[i]);
        }
        
        printf("----------------------\n");
        for (j = 0; j < m; j++) {
            printf("%4d", c_sums[j]);
        }
        printf("  <- column sums\n");

        for (i = 0; i < rows; i++) free(mat[i]);
        free(mat);
        free(r_sums);
        free(c_sums);
    } else {
        printf("\nnot enough elements to form a matrix.\n");
    }
    free(arr);

    end_time = clock();
    work_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("\ntime: %.3f seconds\n", work_time);

    return 0;
}
