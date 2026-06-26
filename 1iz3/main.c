#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int m) {
    int i, j;
    int **mat = (int**)malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) {
        mat[i] = (int*)malloc(m * sizeof(int));
        for (j = 0; j < m; j++) {
            mat[i][j] = rand() % 10;
        }
    }
    return mat;
}

void free_matrix(int **mat, int m) {
    int i;
    if (!mat) return;
    for (i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
}

int matrix_sum(int **mat, int m) {
    int i, j, sum = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            sum += mat[i][j];
        }
    }
    return sum;
}

void print_matrix(FILE *f, int **mat, int m) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            fprintf(f, "%4d", mat[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main(void) {
    int d = 0, mon = 0, y = 0, m, tries = 0;
    int sum1, sum2;
    int **first = NULL, **second = NULL;
    FILE *fin, *fout;
    time_t now;
    struct tm target_date = {0};
    double diff_seconds;
    long diff_days;
    clock_t start_time, end_time;

    start_time = clock();
    srand((unsigned int)time(NULL));

    fin = fopen("input.txt", "r");
    if (!fin) {
        printf("error: no input.txt\n");
        return 1;
    }
    
    if (fscanf(fin, "%d%*c%d%*c%d", &d, &mon, &y) != 3) {
        printf("error: wrong date\n");
        fclose(fin);
        return 1;
    }
    fclose(fin);

    time(&now);
    target_date.tm_mday = d;
    target_date.tm_mon = mon - 1;
    target_date.tm_year = y - 1900;
    target_date.tm_isdst = -1;

    diff_seconds = difftime(mktime(&target_date), now);
    diff_days = (long)(diff_seconds / 86400);
    if (diff_days < 0) diff_days = 0;

    printf("target date: %02d.%02d.%04d\n", d, mon, y);
    printf("days left: %ld\n\n", diff_days);

    printf("enter matrix size M: ");
    if (scanf("%d", &m) != 1 || m < 1) return 1;

    first = create_matrix(m);
    sum1 = matrix_sum(first, m);

    do {
        free_matrix(second, m);
        second = create_matrix(m);
        sum2 = matrix_sum(second, m);
        tries++;
    } while (sum1 != sum2);

    fout = fopen("output.txt", "w");
    if (!fout) return 1;

    fprintf(fout, "target date: %02d.%02d.%04d\n", d, mon, y);
    fprintf(fout, "days left: %ld\n\n", diff_days);
    fprintf(fout, "matrix size: %dx%d. sum: %d\n", m, m, sum1);
    fprintf(fout, "tries: %d\n\n", tries);
    fprintf(fout, "first matrix:\n");
    print_matrix(fout, first, m);
    fprintf(fout, "\nsecond matrix:\n");
    print_matrix(fout, second, m);
    end_time = clock();
    fprintf(fout, "\ntime: %.3f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    fclose(fout);
    
    free_matrix(first, m);
    free_matrix(second, m);
    printf("data saved to output.txt\n");
    return 0;
}
