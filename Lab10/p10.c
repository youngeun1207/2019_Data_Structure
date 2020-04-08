#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 2147483000

typedef struct Node{
	int vertex;
	int dist;
	int prev;
}Node;
typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;
typedef struct Heap{
	int Capacity;
	int size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
int isFull(Heap* heap);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	Graph g;
	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size+1);
	
	char temp = 0;
	while(temp != '\n'){
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
	fclose(fi);
	
	free(g.nodes);
	for(int i = 0; i< g.size; i++) free(g.vertices[i]);
	free(g.vertices);
}

Graph CreateGraph(int size){
	Graph G;
	int j, i;
	G.size = size;
	G.nodes = (Node*)malloc(size * sizeof(Node));
	for(i = 0; i < size; i++){
		G.nodes[i].dist = INT_MAX;
		G.nodes[i].prev = 1; // index 1 (start point)
	}
	G.vertices = (int**)malloc(size * sizeof(int*));
	for(i = 0; i < size; i++){
		G.vertices[i] = (int*)malloc(size * sizeof(int));
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			G.vertices[i][j] = INT_MAX;
		}
	}
	return G;
}

Heap* createMinHeap(int heapSize){
	Heap* heap = malloc(sizeof(Heap));
	heap->Element = malloc(sizeof(Node) * (heapSize + 1));
	heap->Capacity = heapSize;
	heap->size = 0;
	return heap;
}    

int isFull(Heap* heap){
	if(heap->size >= heap->Capacity) return 1;
	return 0;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance){
	int i;
	if(isFull(minHeap)){
		printf("Insertion Error : Heap is Full.\n");
		return;
	}
	for(i = ++minHeap->size; minHeap->Element[i/2].dist > distance; i /= 2){
		minHeap->Element[i] = minHeap->Element[i/2];
	}
	minHeap->Element[i].dist = distance;
	minHeap->Element[i].vertex = vertex;
}

Node deleteMin(Heap* minHeap){
	int i , child;
	Node Min, Last;

	Min = minHeap->Element[1];
	Last = minHeap->Element[minHeap->size--];

	// Build Heap
	for(i = 1; i*2 <= minHeap->size; i = child){
		child = i * 2;
		if(minHeap->Element[child + 1].dist < minHeap->Element[child].dist && child != minHeap->size)
			child++;
		if(Last.dist > minHeap->Element[child].dist)
			minHeap->Element[i] = minHeap->Element[child];
		else 
			break;	
	}
	minHeap->Element[i] = Last;

	return Min;
}

void printShortestPath(Graph g){
	Heap* h = createMinHeap(g.size);

	int* shortestPath = (int*)malloc(g.size * sizeof(int));
	int* visited = (int*)malloc(g.size * sizeof(int));

	g.nodes[1].dist = 0;

	insertToMinHeap(h, 1, 0);

	while(h->size){
		Node node;
		do{
			node = deleteMin(h);
		}while(h->size && visited[node.vertex]);

		if(visited[node.vertex]){
			break;
		}

		visited[node.vertex] = 1;

		for(int i = 0; i < g.size; i++){
			if(g.vertices[node.vertex][i]){
				if(g.nodes[i].dist > g.nodes[node.vertex].dist + g.vertices[node.vertex][i]){
					g.nodes[i].prev = node.vertex;
					g.nodes[i].dist = g.nodes[node.vertex].dist + g.vertices[node.vertex][i];
					insertToMinHeap(h, i, g.nodes[i].dist);
				}
			}
		}
	}
	for(int i = 2; i < g.size; i++){
		if(g.nodes[i].dist == INT_MAX){
			printf("Cannot reach to node %d\n", i);
			continue;
		}
		printf("1->");
		int n = i;
		int count = 0;
		while(g.nodes[n].prev != 1){
			shortestPath[count++] = g.nodes[n].prev;
			n = g.nodes[n].prev;
		}
		for(int j = count - 1; j>= 0; j--){
			printf("%d->", shortestPath[j]);
		}
		printf("%d (cost : %d)\n", i, g.nodes[i].dist);
	}
	free(shortestPath);
	free(visited);
	free(h->Element);
	free(h);
}

