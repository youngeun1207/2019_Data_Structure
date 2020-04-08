#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue{
	int* key;
	int first;
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
	PrintGraph(G);
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


void PrintGraph(Graph G){
	int i, j;
	printf(" ");	
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
	
