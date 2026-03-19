#include <stdio.h>

int main() {
    printf("matrix 3x3:\n");
    double matrix3[3][3];
    double sum1 = 0.0;
    double sum2 = 0.0;

    printf("9 drob for matrix 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%lf", &matrix3[i][j]);
        }
    }
    for (int i = 0; i < 3; i++) {
        sum1 += matrix3[i][i];
        sum2 += matrix3[i][2 - i]; 
    }

    printf("sum1: %.2lf\n", sum1);
    printf("sum2: %.2lf\n\n", sum2);


    printf("matrix 2x2:\n");
    int matrix2[2][2];
    int result[2][2];
    printf("4 cel for matrix 2x2:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matrix2[i][k] * matrix2[k][j];
            }
        }
    }
    printf("kvadrat matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
