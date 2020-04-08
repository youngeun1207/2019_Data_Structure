#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree insertNode(Tree root, int key);
//Tree deleteNode(Tree root, int key);
void findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);
//Tree getMaxValueInTree(Tree parentNode, Tree node);

int main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;

	while (!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch(cv){
		case 'i':
			fscanf(fi, "%d", &key);
			root = insertNode(root, key);
			break;
		/*case 'd':
			fscanf(fi, "%d", &key);
			deleteNode(root, key);
			break;*/
		case 'f':
			fscanf(fi, "%d", &key);
			findNode(root, key);
			break;
		case 'p':
			fscanf(fi, "%c", &cv);
			if(cv == 'i')
				printInorder(root);
			printf("\n");
			break;
		}
	}
	deleteTree(root);
	return 0;
}

Tree insertNode(Tree root, int key)
{
	if(root == NULL){
		root = malloc(sizeof(struct BinarySearchTree));
		if(root == NULL)
		{
			printf("Out of space!");
		}
		else
		{
			root->value = key;
			root->left = NULL;
			root->right = NULL;
			printf("insert %d\n", key);
		}
	}
	else if(key < root->value)
	{
		root->left = insertNode(root->left, key);
	}
	else if(key > root->value)
	{
		root->right = insertNode(root->right, key);
	}
	else // key == root->value
	{
		printf("Insertion Error : There is already %d in the tree\n", key);
	}
	return root;
}

void findNode(Tree root, int key)
{
	if(root == NULL){
		printf("%d is not in the tree\n", key);
	}
	else if(key > root->value)
	{
		findNode(root->right, key);
	}
	else if(key < root->value)
	{
		findNode(root->left, key);
	}
	else // root->value == key
	{
		printf("%d is in the tree\n", key);
	}
}

void printInorder(Tree root)
{
	if(root != NULL)
	{
		printInorder(root->left);
		printf("%d ", root->value);
		printInorder(root->right);
	}
}

void deleteTree(Tree root)
{
	if(root != NULL)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}
