//-----------------------------------------------------------------------------
//  FindPath.c
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
	 	//fprintf(out, "===========1============\n");


	FILE *in, *out;
	char line[MAX_LEN];
	int A, B;
	List path = newList();

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
		addEdge(G, A, B);
	}

	printGraph(out, G);

	while(fgets(line, MAX_LEN, in) != NULL)  {
		A = atoi(strtok(line, " "));
		B = atoi(strtok(NULL, " "));
		if (A == 0 && B == 0) 
			break;
		BFS(G, A);
		if(getDist(G, B) != -1) {
			fprintf(out, "\nThe distance from %d to %d is %d", A, B, getDist(G, B));
			fprintf(out, "\nA shortest %d-%d path is: ", A, B);
			getPath(path, G, B);
			printList(out, path);
			fprintf(out, "\n");
			clear(path);
		}
		else {
			fprintf(out, "\nThe distance from %d to %d is infinity", A, B);
			fprintf(out, "\nNo %d-%d path exists", A, B);
		}
	}

	
	/* close files */
	fclose(in);
	fclose(out);

	return(0);
}