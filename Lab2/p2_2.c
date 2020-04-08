#include<stdio.h>
#include<stdlib.h>

int main(int argv, char** argc)
{
    char name[30];
    printf("enter your name:\n");
    scanf("%[^\n]s", name);
    printf("your name is %s\n", name);

    return 0;
}
