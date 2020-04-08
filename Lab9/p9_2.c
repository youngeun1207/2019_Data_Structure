#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue{
	int* key;
	int front;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(Graph G, int* nodes);
void InsertEdge(Graph G, int a, int b);
void PrintGraph(Graph G);
void DeleteGraph(Graph G);
void Topsort(Graph G);
Queue MakeNewQueue(int x);
int IsEmpty(Queue Q);
int Dequeue(Queue Q, Graph G);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void checkIndegree(int *Indegree, Graph G);
void BubbleSort(int *newInQueue, int index, Graph G);


int main(int argc, char* argv[]){
	int i = 0;
	int* int_node;
	char input_node[MAX];
	char* token;
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	FILE *fi = fopen(argv[1], "r");
	fgets(input_node, MAX, fi);
	int_node = (int*)malloc(sizeof(int)*strlen(input_node)); 
	token = strtok(input_node, " ");
	while(token!=NULL){
		int_node[i++]=atoi(token);
		token = strtok(NULL, " ");
	}
	G->size = i;
	G = CreateGraph(G, int_node);

	while(!feof(fi)){
		fscanf(fi, "%s", input_node);
		token = strtok(input_node, "-");
		if(token == NULL) break;
		int a = atoi(token);
		token = strtok(NULL, " ");
		if(token == NULL) break;
		int b = atoi(token);
		InsertEdge(G,a,b);
	}
	Topsort(G);
	//PrintGraph(G);
	DeleteGraph(G);
	free(int_node);
	fclose(fi);
	return 0;
}

Graph CreateGraph(Graph G, int* nodes){
	int j, i = 0;
	G->node = (int*)malloc(sizeof(int)*G->size); 
	while(nodes[i]){
		G->node[i] = nodes[i];
		i++;
	}
	G->matrix = (int**)malloc(sizeof(int*) * (G->size));
	for(i = 0; i < G->size; i++){
		G->matrix[i] = (int*)malloc(sizeof(int) * (G->size));
	}
	for(i = 0; i < G->size; i++){
		for(j = 0; j < G->size; j++){
			G->matrix[i][j] = 0;
		}
	}
	return G;
}

void InsertEdge(Graph G, int a, int b){
	int i = 0;
	int j = 0;
	while(i < G->size){
		if(a == G->node[i]) break;
		else i++;
	}	
	while(j < G->size){
		if(b == G->node[j]) break;
		else j++;
	}
	G->matrix[i][j] = 1;
}

Queue MakeNewQueue(int x){
	Queue Q = (Queue)malloc(sizeof(struct _Queue));
	Q->key = (int*)malloc(sizeof(int) * x);
	Q->max_queue_size = x;
	Q->rear = -1;
	Q->front = 0;
	Q->qsize = x;
}

void PrintGraph(Graph G){
	int i, j;
	printf("\n ");	
	for(i = 0; i < G->size; i++){
		printf(" %d", G->node[i]);
	}
	printf("\n");
	for(i = 0; i < 6; i++){
		printf("%d ", G->node[i]);
		for(j = 0; j < G->size; j++){
			printf("%d ", G->matrix[i][j]);
		}
		printf("\n");
	}
}

void DeleteGraph(Graph G){
	int i;	
	for(i = 0; i < G->size; i++)
		free(G->matrix[i]);
	free(G->matrix);
	free(G->node);
	free(G);
}

void Topsort(Graph G){
	int V, W, index = 0;
	int newInQueue[G->size];
	int *Indegree;
	Indegree = (int*)malloc(sizeof(int) * G->size);
	Queue Q = MakeNewQueue(G->size);

	checkIndegree(Indegree, G);

	for(V = 0; V < G->size; V++){
		if(Indegree[V] == 0)
			newInQueue[index++] = V;
			//Enqueue(Q, V); // V = index of value in G->nodes
	}
	BubbleSort(newInQueue, index, G);
	for(int i = 0; i < index; i++){
		Enqueue(Q, newInQueue[i]);		
	}
	while(!IsEmpty(Q)){
		index = 0;
		V = Dequeue(Q, G);
		for(W = 0; W < G->size; W++){
			if(G->matrix[V][W] == 1){
				if(--Indegree[W] == 0)
					//Enqueue(Q, W);
					newInQueue[index++] = W;
			}		
		}
		BubbleSort(newInQueue, index, G);
		for(int i = 0; i < index; i++){
			Enqueue(Q, newInQueue[i]);		
		}
	}
	printf("\n");
}

int IsEmpty(Queue Q){
	if(Q->rear < Q->front) return 1;
	return 0;
}

int Dequeue(Queue Q, Graph G){
	int index = Q->key[Q->front];
	printf("%d ", G->node[Q->key[Q->front++]]);
	return index;
}

void Enqueue(Queue Q, int X){
	Q->key[++Q->rear] = X;
}

void checkIndegree(int *Indegree, Graph G){
	int i, j;	
	for(i = 0; i < G->size; i++){
		Indegree[i] = 0;
		for(j = 0; j < G->size; j++)
			Indegree[i] += G->matrix[j][i];
	}
}

void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}

void BubbleSort(int *newInQueue, int index, Graph G){
	int i, j, temp;	
	for(i = 0; i < index; i++){
		for(j = 0; j < index-i-1; j++){
			if(G->node[newInQueue[j]] > G->node[newInQueue[j+1]]){
				temp = newInQueue[j];
				newInQueue[j] = newInQueue[j+1];
				newInQueue[j+1] = temp; 
			}
		}
	}
}
