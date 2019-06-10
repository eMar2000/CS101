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
	int *discover;
	int *finish;
	int *parent;
	int size;
	int order;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->L = malloc((n+1)*sizeof(List));
	G->color = malloc((n+1)*sizeof(int));
	G->parent = malloc((n+1)*sizeof(int));
	G->discover = malloc((n+1)*sizeof(int));
	G->finish = malloc((n+1)*sizeof(int));

	G->order = n;
	G->size = 0;
	
	for(int i = 1; i <= n; i++) {
		G->L[i] = newList();
		G->color[i] = 0;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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
	for (int i = 1; i <= G->order; i++) {
		freeList(&G->L[i]);
		free(G->L[i]);
	}
	free(G->L);
	free(G->color);
	free(G->discover);
	free(G->finish);
	free(G->parent);
	G->L = NULL;
	G->color = NULL;
	G->parent = NULL;
	G->discover = NULL;
	G->finish = NULL;
	free(G);
	G->order = 0;
	*pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getOrder() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getSize() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getParent(Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getParent() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getParent() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getDiscover() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getDiscover() u out of bounds\n");
		exit(EXIT_FAILURE);
	}
	return G->discover[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: getFinish() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: getFinish() u out of bounds\n");
		exit(EXIT_FAILURE);
	}

	return G->finish[u];
}

void addEdge(Graph G, int u, int v) {
	if (G == NULL){
		fprintf(stderr, "Graph Error: addEdge() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: addEdge() u out of bounds\n");
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
		fprintf(stderr, "Graph Error: addArc() called on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: addArc() u out of bounds\n");
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

int Visit(Graph G, int x, int time, List L) {
	int y;
	G->discover[x] = ++time;

	G->color[x] = 1;
	moveFront(G->L[x]);
	while (index(G->L[x]) != -1) {
		y = get(G->L[x]);
		if (G->color[y] == 0) {
			G->parent[y] = x;
			time = Visit(G, y, time, L);
		}
		moveNext(G->L[x]);
	}
	G->color[x] = 2;
	G->finish[x] = ++time;
	prepend(L, x);
	return time;
}

/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S) {
	if (length(S)!=getOrder(G)) {
		fprintf(stderr, "Graph Error: DFS() called with wrong order\n");
		return;
	}

	for (int i = 1; i <= G->order; i++) {
		G->color[i] = 0;
		G->parent[i] = NIL;
	}
	int time = 0;
	List L = copyList(S);
	moveFront(S);
	while (index(S) != -1) {
		deleteBack(S);
	}
	moveFront(L);
	while (index(L) != -1) {
		if (G->color[get(L)] == 0)
			time = Visit(G, get(L), time, S);
		moveNext(L);
	}
	freeList(&L);
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

	fprintf(out, "Adjacency list representation of G:\n");
	for(int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->L[i]);
		fprintf(out, "\n");
	}
}

Graph transpose(Graph G) {
	Graph A = newGraph(G->order);

	A->order = G->order;
	A->size = G->size;
	
	for(int i = 1; i <= G->order; i++) {
		moveFront(G->L[i]);
		while (index(G->L[i]) != -1) {
			addArc(A, get(G->L[i]), i);
			moveNext(G->L[i]);
		}
	}
	return A;
}

Graph copyGraph(Graph G) {
	Graph A = newGraph(G->order);

	A->order = G->order;
	A->size = G->size;
	
	for(int i = 1; i <= G->order; i++) {
		A->L[i] = G->L[i];
		A->color[i] = G->color[i];
		A->discover[i] = G->discover[i];
		A->finish[i] = G->finish[i];
		A->parent[i] = G->parent[i];
	}
	return A;
}

