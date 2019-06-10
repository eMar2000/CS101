//-----------------------------------------------------------------------------
//  Graph.c
//  Name: Eric Mar
//  CruzID: emmar
//
//  Graph adt
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Graph.h" // Include user-defined header file

/*
 * Graph Structure
 */
typedef struct GraphObj{
	List *L;
	int *color;
	int *distance;
	int *parent;
	int size;
	int order;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->L = malloc((n+1)*sizeof(List));
	G->color = malloc((n+1)*sizeof(int));
	G->parent = malloc((n+1)*sizeof(int));
	G->distance = malloc((n+1)*sizeof(int));

	G->order = n;
	G->size = 0;
	G->source = 0;
	
	for(int i = 1; i <= n; i++) {
		G->L[i] = newList();
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	return G;
}

void freeGraph(Graph* pG) {
	if (pG == NULL){
		fprintf(stderr, "Graph Error: freeGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if (*pG == NULL){
		return;
	}

	Graph G = *pG;

	G->size = 0;
	G->source = 0;
	for (int i = 1; i <= G->order; i++) {
		freeList(&G->L[i]);
		free(G->L[i]);
	}
	free(G->L);
	free(G->color);
	free(G->distance);
	free(G->parent);
	G->L = NULL;
	G->color = NULL;
	G->parent = NULL;
	G->distance = NULL;
	free(G);
	G->order = 0;
	*pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getSource(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	 
	return G->source;
}

int getParent(Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getParent() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

int getDist(Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getDist() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}

void getPath(List L, Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getPath() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL) {
		fprintf(stderr, "Graph Error: getPath() no source\n");
		exit(EXIT_FAILURE);
	}
	int s = getSource(G);
	if (u == s) {
		append(L, s);
	}
	else if (G->parent[u] == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	G->size = 0;
	for(int i = 1; i <= G->order; i++) {
		freeList(&G->L[i]);
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
}

void addEdge(Graph G, int u, int v) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getPath() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Graph Error: addEdge() v out of bounds\n");
		exit(EXIT_FAILURE);
	}

	moveFront(G->L[u]);
	while (index(G->L[u]) != -1 && v > get(G->L[u])){
		moveNext(G->L[u]);
	}

	if (index(G->L[u]) != -1)
		insertBefore(G->L[u], v);
	else
		append(G->L[u], v);

	moveFront(G->L[v]);
	while (index(G->L[v]) != -1 && u > get(G->L[v]))
		moveNext(G->L[v]);

	if (index(G->L[v]) != -1)
		insertBefore(G->L[v], u);
	else
		append(G->L[v], u);

	G->size++;
}

void addArc(Graph G, int u, int v) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getPath() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Graph Error: addArc() v out of bounds\n");
		exit(EXIT_FAILURE);
	}

	moveFront(G->L[u]);
	while (index(G->L[u]) != -1 && v > get(G->L[u]))
		moveNext(G->L[u]);

	if (index(G->L[u]) != -1)
		insertBefore(G->L[u], v);
	else
		append(G->L[u], v);

	G->size++;
}

void BFS(Graph G, int s) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i <= G->order; i++) {
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	int x, y = 0;
	G->color[s] = 1;
	G->distance[s] = 0;
	List L = newList();
	append(L,s);
	moveFront(L);
	while (length(L) > 0) {
		x = front(L);
		deleteFront(L);
		moveFront(G->L[x]);
		while (index(G->L[x]) != -1) {
			y = get(G->L[x]);
			if (G->color[y] == 0) {
				G->color[y] = 1;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(L,y);
			}
			G->color[x] = 2;
			moveNext(G->L[x]);
		}
	}
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}

	if (out == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL out reference\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->L[i]);
		fprintf(out, "\n");
	}
}
