#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<setjmp.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

static jmp_buf env;

Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key, bool flag);
void findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);
Tree getMaxValueInTree(Tree parentNode, Tree node);

int main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;
	setjmp(env);	
	while (!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch(cv){
		case 'i':
			fscanf(fi, "%d", &key);
			root = insertNode(root, key);
			break;
		case 'd':
			fscanf(fi, "%d", &key);
			root = deleteNode(root, key, 1);
			break;
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

Tree getMaxValueInTree(Tree parentNode, Tree node)
{
	if(parentNode == NULL)
		return NULL;

	else if(node == NULL)
		return parentNode;

	else
		return getMaxValueInTree(node, node->right);
}

Tree deleteNode(Tree root, int key, bool flag)
{
	Tree TmpCell;
	
	if(root == NULL){
		printf("Deletion Error : %d is not in the tree.\n", key);
		longjmp(env,1); // break out from all recursion
	}
	else if(key < root->value){
		root->left = deleteNode(root->left, key, 0);
	}
	else if(key > root->value){
		root->right = deleteNode(root->right, key, 0);
	}
	else if(root->right != NULL && root->left != NULL) // have both children
	{
		TmpCell = getMaxValueInTree(root, root->left);
		root->value = TmpCell->value;
		root->left = deleteNode(root->left, root->value, 0);
	}
	else // have 1 or 0 child
	{
		TmpCell = root;
		if(root->left == NULL){
			root = root->right;
		}
		else if(root->right == NULL){
			root = root->left;
		}
		free(TmpCell);
	}
	if(flag){
		printf("delete %d\n", key);
	}
	return root;		
}
