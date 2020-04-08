#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
typedef int ElementType;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node
{
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void PrintList(List L);
void Insert(ElementType X, List L, Position P);

int main(int argc, char * argv[])
{
    char command;
    int key1, key2;
    FILE *input;
    Position header;
    Position tmp;
    if(argc == 1)
    {
        printf("No input file\n");
        return 0;
    }
    else
        input = fopen(argv[1], "r");
    header = MakeEmpty(header);
    while(1){
        command = fgetc(input);
        if(feof(input)) break;
        switch(command) {
        case 'i':
            fscanf(input, "%d %d", &key1, &key2);
            Insert(key1, header, header);
            break;
        case 'p':
            PrintList(header);
            break;
        default:
            break;
        }
    }
    fclose(input);
    
    return 0;
}

List MakeEmpty(List L)
{
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    
    if(P == NULL)
    {
        printf("Insertion(%d) Failed : cannot find the location to be inserted\n", X);
        return;
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}


void PrintList(List L)
{
    Position P;
    P = L->Next;
    if(P == NULL)
        printf("your list is empty.\n");
    while(P != NULL)
    {
        printf("key:%d\t", P->Element);
        P = P->Next;
    }
    printf("\n");
}
