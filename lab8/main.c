#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct human
{
    char surname[50];
    char name[50];
    int year;
    char sex[10];
    double height;
};

int sortFields[4];
int sortCount;

int compareHumans(const void *a, const void *b)
{
    const struct human *x = (const struct human *)a;
    const struct human *y = (const struct human *)b;
    int i, result;

    for (i = 0; i < sortCount; i++)
    {
        switch (sortFields[i])
        {
            case 1:
                if (x->year < y->year) return -1;
                if (x->year > y->year) return 1;
                break;

            case 2:
                result = strcmp(x->surname, y->surname);
                if (result != 0) return result;
                result = strcmp(x->name, y->name);
                if (result != 0) return result;
                break;

            case 3:
                result = strcmp(x->sex, y->sex);
                if (result != 0) return result;
                break;

            case 4:
                if (x->height < y->height) return -1;
                if (x->height > y->height) return 1;
                break;
        }
    }

    return 0;
}

int main()
{
    struct human people[100];
    int n, i, count = 0;
    FILE *file, *out;

    file = fopen("input.txt", "w");
    if (file == NULL)
    {
        printf("ERROR create input.txt\n");
        return 1;
    }

    printf("number of lines? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("enter surname, name, year, pol, rost: ");
        scanf("%49s %49s %d %9s %lf",
              people[i].surname,
              people[i].name,
              &people[i].year,
              people[i].sex,
              &people[i].height);

        fprintf(file, "%s %s %d %s %.2lf\n",
                people[i].surname,
                people[i].name,
                people[i].year,
                people[i].sex,
                people[i].height);
    }

    fclose(file);

    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("ERROR open input.txt\n");
        return 1;
    }

    while (fscanf(file, "%49s %49s %d %9s %lf",
                  people[count].surname,
                  people[count].name,
                  &people[count].year,
                  people[count].sex,
                  &people[count].height) == 5)
    {
        count++;
    }

    fclose(file);

    printf("sorted lines:\n");
    printf("1 - year\n");
    printf("2 - surname name\n");
    printf("3 - pol\n");
    printf("4 - rost\n");

    printf("skolko lines ");
    scanf("%d", &sortCount);

    for (i = 0; i < sortCount; i++)
    {
        printf("number of line %d: ", i + 1);
        scanf("%d", &sortFields[i]);
    }

    qsort(people, count, sizeof(struct human), compareHumans);

    printf("sorted:\n");
    for (i = 0; i < count; i++)
    {
        printf("%s %s %d %s %.2lf\n",
               people[i].surname,
               people[i].name,
               people[i].year,
               people[i].sex,
               people[i].height);
    }

    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("ERROR create output.txt\n");
        return 1;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(out, "%s %s %d %s %.2lf\n",
                people[i].surname,
                people[i].name,
                people[i].year,
                people[i].sex,
                people[i].height);
    }

    fclose(out);

    return 0;
}
