//-----------------------------------------------------------------------------
//  Lex.c
//  Name: Eric Mar
//  CruzID: emmar
//
//  Creates lexographically ordered list derived from given set of elements
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h" // Include user-defined header file

#define MAX_LEN 160

int main(int argc, char * argv[]){

	List L = newList();

	int n, count=0;
	FILE *in, *out, *in2;
	char line[MAX_LEN];
	char* token;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	in2 = fopen(argv[1], "r");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	while( fgets(line, MAX_LEN, in2) != NULL)  
		n++;
	char tokenlist[n][MAX_LEN];

	/* read each line of input file, then count and print tokens */
	while( fgets(line, MAX_LEN, in) != NULL)  {
		token = strtok(line, "\n");
		tokenlist[count][0] = '\0';
		while( token!=NULL ){
			strcat(tokenlist[count], token);
			token = strtok(NULL, "\n");
			count++;
		}
	}

	for(int i = 1; i < count; i++){
		if (length(L) == 0)
			prepend(L, 0);
		moveFront(L);
		do{
			int x = strcmp(&tokenlist[i][0], &tokenlist[get(L)][0]);

			if (x <= 0){
				insertBefore(L, i);
				break;                                            // Break
			}
			else
				moveNext(L);
			if (index(L) == -1) {
				append(L, i);
			}
		}while (index(L) != -1);

	}

	// printList(out, L);
	moveFront(L);
	while(index(L) != -1) {                                      //Print
		fprintf(out, "%s\n", &tokenlist[get(L)][0]);
		moveNext(L);
	}

	freeList(&L);
	for(int i = 0; i < count; i++) {
		free(tokenlist[i]);
	}
	free(tokenlist);

	/* close files */
	fclose(in);
	fclose(in2);
	fclose(out);

	return(0);
}