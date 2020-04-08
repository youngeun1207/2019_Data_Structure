#include<stdio.h>
#include<stdlib.h>
typedef struct CompleteTree* Tree;
struct CompleteTree{
    int Size;
    int nodeNum;
    int* Element;
};


Tree CreateTree(int treeSize);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);
void freeTree(Tree tree);
    
void main(int argc, char* argv[])
{
    FILE *fi;
    Tree tree;
    int treeSize;
    int tempNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);
    while(fscanf(fi, "%d", &tempNum) == 1)
    {
        Insert(tree, tempNum);
    }
    PrintTree(tree);
    freeTree(tree);
}

Tree CreateTree(int treeSize){
    Tree tree = (Tree)malloc(sizeof(struct CompleteTree));
    tree->Element = (int*)malloc(sizeof(int) * (treeSize + 1));
    tree->Size = treeSize;
    tree->nodeNum = 0;
    return tree;
}

void Insert(Tree tree, int value){
    if(tree->nodeNum + 1 > tree->Size){
        printf("Error! Tree is Full.\n");
        return;
    }
    tree->Element[++tree->nodeNum] = value;
}

void PrintTree(Tree tree){
    printf("Preorder : ");
    printPreorder(tree, 1);
    printf("\n");
    printf("Inorder : ");
    printInorder(tree, 1);
    printf("\n");
    printf("Postorder : ");
    printPostorder(tree, 1);
    printf("\n");
    
}

void printPreorder(Tree tree, int index){
    if(tree->Element[index] && index <= tree->Size){
        printf(" %d", tree->Element[index]);
        printPreorder(tree, 2 * index);
        printPreorder(tree, 2 * index + 1);
    }
}

void printInorder(Tree tree, int index){
    if(tree->Element[index] && index <= tree->Size){
        printInorder(tree, 2 * index);
        printf(" %d", tree->Element[index]);
        printInorder(tree, 2 * index + 1);
    }
}

void printPostorder(Tree tree, int index){
    if(tree->Element[index] && index <= tree->Size){
        printPostorder(tree, 2 * index);
        printPostorder(tree, 2 * index + 1);
        printf(" %d", tree->Element[index]);
    }
}

void freeTree(Tree tree){
    free(tree->Element);
    free(tree);
}
    

