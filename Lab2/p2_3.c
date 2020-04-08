#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char ** argv)
{
    int n = atoi(argv[1]);
    char *input = (char*)malloc(sizeof(char) * 31 * n);
    // the length of name is up to 30 characters
    char **name = (char**)calloc(n, sizeof(char*));
    
    printf("enter %d names:\n", n);
    scanf("%[^\n]s", input);
    char *ptr = strtok(input, " ");    
   
    printf("the names you entered:\n");

    int i = 0;
    while(ptr != NULL)
    {
        name[i] = (char*)calloc(strlen(ptr) + 1, sizeof(char));
        strcpy(name[i], ptr);
        i++;
        ptr = strtok(NULL, " ");
    }
    
    int j;
    for(j = 0; j < n; j++)
    {
        printf("%s\n", name[j]);
        free(name[j]);
    }
    free(name);
    free(input);

    return 0;
}    


    
