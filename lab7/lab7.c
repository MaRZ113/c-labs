#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct humen
{
    char surname[50];
    char name[50];
    int year;
};

int main()
{
	FILE *in;
    struct humen *a, *b, temp;
    int count = 0;
    int i, j;
    char s[50], n[50];
    int y;
    in = fopen("input.txt", "r");
    if (in == NULL)
    {
    	printf("ERROR open input.txt");
    	return 1;
	}
	while (fscanf(in, "%49s %49s %d", s, n, &y) == 3) {
		count++;
	}
	if (count == 0)
	{
		printf("file empty");
		fclose(in);
		return 1;
	}
	
	a = (struct humen *)malloc(count * sizeof(struct humen));
	b = (struct humen *)malloc(count * sizeof(struct humen));
	
	if (a == NULL || b == NULL)
	{
		printf("ERROR malloc");
		fclose(in);
		free(a);
		free(b);
		return 1;
	}
	
	rewind(in);
	for (i = 0; i < count; i++)
	{
		if (fscanf(in, "%49s %49s %d", a[i].surname, a[i].name, &a[i].year) != 3)
		{
			printf("ERROR reading");
			fclose(in);
		    free(a);
		    free(b);
		    return 1;
		}
	}
	fclose(in);
	for (i = 0; i  < count - 1; i++)
	{
		b[i] = a[i];
	}
	for (i = 0; i < count - 1; i++)
    {
    	for (j = 0; j < count - 1 - i; j++)
    	{
    		if (b[j].year > b[j + 1].year)
    		{
    			temp = b[j];
    			b[j] = b[j + 1];
    			b [j + 1] = temp;
			}
		}
		
		printf("initial massiv: \n");
		for (i = 0; i < count; i++)
		{
			printf("sorted massiv: \n");
			for (i = 0; i < count; i++)
			{
				printf("%s %s %d\n", b[i].surname, b[i].name, b[i].year);
			}
			free(a);
			free(b);
		}
    return 0;
    }
}
