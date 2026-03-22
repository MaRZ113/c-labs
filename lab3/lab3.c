#include <stdio.h>

int main() {
char str[85]; 
    int i;
    printf("your ab string:\n");
    fgets(str, sizeof(str), stdin);
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') {
            str[i] = 'A';
        } else if (str[i] == 'b') {
            str[i] = 'B';
        }
    }
    printf("your ab CAPS string:\n%s", str);
    return 0;
}
