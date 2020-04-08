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
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void PrintList(List L);
void Delete(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);

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
            tmp = Find(key2, header); 
            Insert(key1, header, tmp);
            break;
        case 'd':
            fscanf(input, "%d", &key1);
            Delete(key1, header);
            break;
        case 'f':
            fscanf(input, "%d", &key1);
            tmp = FindPrevious(key1, header);
            if(IsLast(tmp, header))
                printf("Could not find %d in the list\n", key1);
            else{
                if(tmp->Element > 0)
                    printf("Key of the previous node of %d is %d.\n", key1, tmp->Element);
                else
                    printf("Key of the previous node of %d is header.\n", key1);
            }
            break;
        case 'p':
            PrintList(header);
            break;
        default:
            break;
        }
    }
    DeleteList(header);
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

Position Find(ElementType X, List L)
{
    Position P;
    if(X == -1)
        return L;
    P = L->Next;
    while(P != NULL && P->Element != X)
        P = P->Next;
    return P;
}

Position FindPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while(P->Next != NULL && P->Next->Element != X)
        P = P->Next;
    return P;
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    
    if(P == NULL)
    {
        printf("Insertion(%d) Failed : cannot fint the location to be inserted\n", X);
        return;
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X,L);
    if(!IsLast(P,L))
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
    else
        printf("Deletion failed : element %d is not in the list\n", X);
}

void DeleteList(List L)
{
    Position P, Tmp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

void PrintList(List L)
{
    Position P;
    P = L->Next;
    if(P == NULL)
        printf("your list is empty.");
    while(P != NULL)
    {
        printf("key:%d\t", P->Element);
        P = P->Next;
    }
    printf("\n");
}
