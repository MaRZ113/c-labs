#include <stdio.h>
#include <string.h>

struct humen
{
    char surname[50];
    char name[50];
    int year;
};

int main()
{
    struct humen a[4];
    struct humen b[4];
    struct humen temp;
    int i, j;

    for (i = 0; i < 4; i++)
    {
        printf("Enter surname: ");
        scanf("%49s", a[i].surname);

        printf("Enter name: ");
        scanf("%49s", a[i].name);

        printf("Enter year: ");
        scanf("%d", &a[i].year);
    }

    for (i = 0; i < 4; i++)
    {
        b[i] = a[i];
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3 - i; j++)
        {
            if (b[j].year > b[j + 1].year)
            {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    printf("\nSorted:\n");
    for (i = 0; i < 4; i++)
    {
        printf("%s %s %d\n", b[i].surname, b[i].name, b[i].year);
    }

    return 0;
}
