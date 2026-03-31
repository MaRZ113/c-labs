#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *in_file;
    FILE *out_file;
    char last_name[50];
    char first_name[50];
    char patronymic[50];
    int year;

    in_file = fopen("people.txt", "w");
    if (in_file == NULL) {
        printf("ERROR!\n");
        return 1;
    }
    fprintf(in_file, "Ivanov 1975\n");
    fprintf(in_file, "Sidorov 1981\n");
    fprintf(in_file, "Vorobyaninov 1978\n");
    fprintf(in_file, "Petrova 1990\n");
    fprintf(in_file, "Smirnov 1979\n");
    fclose(in_file);

    printf("'people.txt' created.\n");

    in_file = fopen("people.txt", "r");
    out_file = fopen("young_people.txt", "w");

    if (in_file == NULL || out_file == NULL) {
        printf("ERROR opening!\n");
        return 1;
    }

    while (fscanf(in_file, "%49s %49s %49s %d", last_name, first_name, patronymic, &year) == 4) {
        if (year > 1980) {
            fprintf(out_file, "%s %s %s %d\n", last_name, first_name, patronymic, year);
        }
    }

    fclose(in_file);
    fclose(out_file);

    printf("'young_people.txt' filtered and created succesfully!\n");

    return 0;
}
