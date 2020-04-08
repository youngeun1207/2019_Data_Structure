#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
//int Pop(Stack* S);
//int Top(Stack* S);
int IsFull(Stack* S);

void main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    
    Stack* stack;
    char input_str[101];
    int max, i = 0, a, b, result;

    fgets(input_str, 101, fi);
    max = 10;
    stack = CreateStack(max);

    for(i = 0; i < strlen(input_str) && input_str[i] != '#'; i++)
    {
        Push(stack, input_str[i]);
    }
    fclose(fi);
    //DeleteStack(stack);
}

Stack* CreateStack(int max){
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(struct Stack));
    S->key = (int*)malloc(sizeof(int) * max);
    S->max_stack_size = max;
    S->top = -1;
    return S;
}

void Push(Stack* S, int X)
{
    if(IsFull(S)){
        printf("error : Full stack\n");
        return;
    }
    else if(S == NULL){
        printf("error : No stack exists\n");
        return;
    }
    else{
        S->top++;
        S->key[S->top] = X;
        printf("%c inserted\n", X);
    }
}

int IsFull(Stack* S)
{
    if(S->top >= S->max_stack_size-1)
        return 1;
    return 0;
}
