#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct HeapStruct
{
    int Capacity;
    int Size;
    int *Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap, int value);
int Find(Heap* heap, int value);
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while(!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch(cv){
		case 'n' :
			fscanf(fi, "%d", &heapSize);
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i' :
			fscanf(fi, "%d", &key);
			Insert(maxHeap, key);
			break;
		case 'd':
			key = DeleteMax(maxHeap);
			break;
		case 'p':
			PrintHeap(maxHeap);
			break;
		case 'f' :
			fscanf(fi, "%d", &key);
			if(Find(maxHeap, key))
				printf("%d is in the tree.\n", key);
			else
				printf("%d is not in the tree.\n", key);
			break;
		default:
			break;
		}
	}
}

Heap* CreateHeap(int heapSize){
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if(heap == NULL){
		printf("Out of Space\n");
		return NULL;
	}
	heap->Element = (int*)malloc(sizeof(int) * (heapSize + 1));
	if(heap->Element == NULL){
		printf("Out of Space\n");
		return NULL;
	}
	heap->Capacity = heapSize;
	heap->Element[0] = INT_MAX;
	heap->Size = 0;
	return heap;
}    

void Insert(Heap* heap, int value){
	int i;
	if(heap->Capacity <= heap->Size){
		printf("Insertion Error : Max Heap is Full.\n");
		return;
	}
	if(Find(heap, value)){
		printf("%d is already in the tree\n", value);
		return;
	}
	for(i = ++heap->Size; heap->Element[i/2] < value; i /= 2)
		heap->Element[i] = heap->Element[i/2];
	heap->Element[i] = value;
	printf("insert %d\n", value);
}

int Find(Heap* heap, int value){
	int i;
	for(i = 1; i <= heap->Size; i++){
		if(heap->Element[i] == value)
			return 1;
	}
	return 0;
}

int DeleteMax(Heap* heap){
	int i, Child;
	int Max, Last;

	if(heap->Size == 0){
		printf("Deletion Error : Max heap is empty!\n");
		return NULL;
	}
	Max = heap->Element[1];
	Last = heap->Element[heap->Size--];
	
	for(i = 1; i * 2 <= heap->Size; i = Child){
		Child = i * 2;
		if(Child != heap->Size && heap->Element[Child + 1] > heap->Element[Child])
			Child++;
		if(Last < heap->Element[Child])
			heap->Element[i] = heap->Element[Child];
		else break;
	}
	heap->Element[i] = Last;
	printf("Max Element: %d deleted\n", Max);
	return Max;
}

void PrintHeap(Heap* heap){
	int i;
	if(heap->Size == 0){
		printf("Print Error : Max heap is empty!\n");
		return;
	}
	for(i = 1; i <= heap->Size; i++)
		printf("%d ", heap->Element[i]);
	printf("\n");
}
		
