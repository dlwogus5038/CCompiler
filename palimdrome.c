#include <stdio.h>
#include <string.h>

int test(char* s, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        if (s[i] != s[j]) return 0;
        i++;
        j--;
    }
    return 1;
}

int main() {
    char s[200];
    printf("Enter the string to test: ");
    scanf("%s", s);
    if (test(s, strlen(s))) printf ("The string is palindromic.\n");
    else printf ("The string is not palindromic.\n");
    return 0;
}