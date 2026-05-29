#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1. Создать текстовый файл с записями: год, имя, фамилия, пол и рост (в метрах)
2. Записи вводятся с клавиатуры пользователем
3. Упорядочить
4. Указать, по чему упорядочиваются через консоль: год, имя, фамилия, пол или рост
5. Возможность задавать несколько полей для упорядоч.
*/

#define MAX_RECORDS 100
#define STR_LEN     64
#define FILENAME    "people.txt"

typedef struct {
    char name[STR_LEN];
    char surname[STR_LEN];
    int  year;
    char sex[STR_LEN];
    double height;
}  Person;

static char keys[8][STR_LEN];
static int  key_count = 0;

int input_records(const char *filename)
{
    int    n;
    int    i;
    FILE  *f;
    char   name[STR_LEN];
    char   surname[STR_LEN];
    char   sex[STR_LEN];
    int    year;
    double height;

    printf("kol-vo zapisei ");
    if (scanf("%d", &n) != 1) {
        printf("ERROR. input w number\n");
        return -1;
    }
    if (n < 1) n = 1;
    if (n > MAX_RECORDS) n = MAX_RECORDS;

    f = fopen(filename, "w");
    if (f == NULL) {
        printf("ERROR file create %s\n", filename);
        return -1;
    }

    for (i = 0; i < n; i++) {
        printf("\ninput %d:\n", i + 1);

        printf("name: ");
        scanf("%63s", name);

        printf("surname: ");
        scanf("%63s", surname);

        printf("year: ");
        scanf("%d", &year);

        printf("m/f: ");
        scanf("%63s", sex);

        printf("height (format x.xx): ");
        scanf("%lf", &height);

        fprintf(f, "%s %s %d %s %.2f\n", name, surname, year, sex, height);
    }

    fclose(f);
    return n;
}

int read_file(const char *filename, Person people[], int max)
{
    FILE *f;
    int   count = 0;

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("ERROR file %s\n", filename);
        return -1;
    }

    while (count < max &&
           fscanf(f, "%63s %63s %d %63s %lf",
                  people[count].name,
                  people[count].surname,
                  &people[count].year,
                  people[count].sex,
                  &people[count].height) == 5) {
        count++;
    }

    fclose(f);
    return count;
}

int compare_field(const Person *a, const Person *b, const char *key)
{
    if (strcmp(key, "year") == 0) {
        return a->year - b->year;
    } else if (strcmp(key, "name") == 0) {
        return strcmp(a->name, b->name);
    } else if (strcmp(key, "surname") == 0) {
        return strcmp(a->surname, b->surname);
    } else if (strcmp(key, "sex") == 0) {
        return strcmp(a->sex, b->sex);
    } else if (strcmp(key, "height") == 0) {
        if (a->height < b->height) return -1;
        if (a->height > b->height) return  1;
        return 0;
    }
    return 0;
}

int compare_persons(const void *pa, const void *pb)
{
    const Person *a = (const Person *)pa;
    const Person *b = (const Person *)pb;
    int i;
    int r;

    for (i = 0; i < key_count; i++) {
        r = compare_field(a, b, keys[i]);
        if (r != 0) {
            return r;
        }
    }
    return 0;
}

void print_people(const Person people[], int count)
{
    int i;

    printf("\n%-12s %-15s %-6s %-5s %-7s\n",
           "name", "surname", "year", "m/f", "height");
    for (i = 0; i < count; i++) {
        printf("%-12s %-15s %-6d %-5s %-7.2f\n",
               people[i].name,
               people[i].surname,
               people[i].year,
               people[i].sex,
               people[i].height);
    }
}

int main(void)
{
    Person people[MAX_RECORDS];
    int count;
    char line[256];
    int c;
    char *token;
    int i;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (input_records(FILENAME) < 0) {
        return 1;
    }

    count = read_file(FILENAME, people, MAX_RECORDS);
    if (count <= 0) {
        printf("no sort strings.\n");
        return 1;
    }

    printf("\ninput data:\n");
    print_people(people, count);

    printf("\nstrings for sorting: 1 to 5 - name surname year sex height\n");
    printf("input sort string: ");

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("ERROR input\n");
        return 1;
    }

    token = strtok(line, " ");
    while (token != NULL && key_count < 8) {
        strncpy(keys[key_count], token, STR_LEN - 1);
        keys[key_count][STR_LEN - 1] = '\0';
        key_count++;
        token = strtok(NULL, " ");
    }

    if (key_count == 0) {
        strcpy(keys[0], "year");
        key_count = 1;
        printf("default sort by: year\n");
    }

    printf("\nsorted result:");
    for (i = 0; i < key_count; i++) {
        printf(" %s", keys[i]);
    }
    printf("\n");

    qsort(people, count, sizeof(Person), compare_persons);

    print_people(people, count);

    return 0;
}
