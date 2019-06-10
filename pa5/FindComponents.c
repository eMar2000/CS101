//-----------------------------------------------------------------------------
//  FindComponents.c
//  Name: Eric Mar
//  CruzID: emmar
//
//  Graph client
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h" // Include user-defined header file
#define MAX_LEN 10

int main(int argc, char * argv[]){

	FILE *in, *out;
	char line[MAX_LEN];
	int A, B;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	Graph G = newGraph(atoi(fgets(line, MAX_LEN, in)));

	while(fgets(line, MAX_LEN, in) != NULL)  {
		A = atoi(strtok(line, " "));
		B = atoi(strtok(NULL, " "));

		if (A == 0 && B == 0) 
			break;
		addArc(G, A, B);
	}

	printGraph(out, G);

	List L = newList();
	for (int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	DFS(G, L);
	Graph T = transpose(G);
	DFS(T, L);

	int count = 0;
	for (int i = 1; i <= getOrder(G); i++) 
		if(getParent(T, i) == NIL) 
			count++;

	fprintf(out, "\nG contains %d strongly connected components:", count);

	List components = newList();
	for (int i = 1; i <= count; i++) {
		fprintf(out, "\nComponent %d: ", i);

		moveBack(L);
		while (getParent(T, get(L)) != NIL) {
			prepend(components, get(L));
			delete(L);
			moveBack(L);
		}

		prepend(components, get(L));
        delete(L);
		printList(out, components);
		moveFront(components);
		while (index(components) != -1) {
			deleteBack(components);
		}
	}
	fprintf(out, "\n");

	
	/* close files */
	fclose(in);
	fclose(out);

	return(0);
}