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
int Pop(Stack* S);
int Top(Stack* S);
void DeleteStack(Stack* S);
int IsEmpty(Stack* S);
int IsFull(Stack* S);
int Postfix(Stack* S, char input_str);

void main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    
    Stack* stack;
    char input_str[101];
    int max, i = 0, a, b, result;

    fgets(input_str, 101, fi);
    max = 10;
    stack = CreateStack(max);

    printf("Top numbers : ");

    for(i = 0; i < strlen(input_str) && input_str[i] != '#'; i++)
    {
        result = Postfix(stack, input_str[i]);
    }
    printf("\nevaluation result : %d\n", result);
    fclose(fi);
    DeleteStack(stack);
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
        printf("error : Full stack ");
        return;
    }
    else{
        S->top++;
        S->key[S->top] = X;
    }
}

int IsFull(Stack* S)
{
    if(S->top >= S->max_stack_size-1)
        return 1;
    return 0;
}

int Postfix(Stack* stack, char input_char)
{
    int a,b;
    int result, temp;
    switch(input_char){
        case '+':
            b = Pop(stack);
            a = Pop(stack);
            result = a + b;
            break;
        case '-':
            b = Pop(stack);
            a = Pop(stack);
            result = a - b;
            break;
        case '*':
            b = Pop(stack);
            a = Pop(stack);
            result = a * b;
            break;
        case '/':
            b = Pop(stack);
            a = Pop(stack);
            result = a / b;
            break;
        case '%':
            b = Pop(stack);
            a = Pop(stack);
            result = a % b;
            break;
        default:
            temp = input_char - '0';
            Push(stack, temp);
            printf("%c ", input_char);
            return 0;
    }
    Push(stack, result);
    printf("%d ",Top(stack));
    return result;
}

int Pop(Stack* S)
{
    if(IsEmpty(S)){
        printf("Error : Empty stack ");
        return 0;
    }
    else{
        int temp = S->key[S->top];
        S->top--;
        return temp;
    }
}

int Top(Stack* S){
    if(!IsEmpty(S))
        return S->key[S->top];
    else{
        return 0;
    }
}

int IsEmpty(Stack* S){
    if(S->top < 0){
        return 1;
    }
    return 0;
}

void DeleteStack(Stack* S){
    if(S == NULL){
        return;
    }
    free(S->key);
    free(S);
}

