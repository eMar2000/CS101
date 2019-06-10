//-----------------------------------------------------------------------------
//  List.c
//  Name: Eric Mar
//  CruzID: emmar
//
//  List ADT with get functions, comparison function, list modification function
//  List transversal function, list copy function, and print function.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "List.h" // Include user-defined header file

/*
 * Node Structure
 */
typedef struct NodeObj{
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

/*
 * List Structure
 */
typedef struct ListObj{
   struct NodeObj* cursor;
   struct NodeObj* front;
   struct NodeObj* back;
   int index;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

void freeNode(Node *n) {
	if (n != NULL && *n != NULL) {
		free(*n);
		*n = NULL;
	}
}

Node newNode(int d) {
	Node x = malloc(sizeof(NodeObj));
	x->data = d;
	x->prev = NULL;
	x->next = NULL;
	return x;
}

List newList(void) {
	List temp = malloc(sizeof(ListObj));
	temp->front = NULL;
	temp->back = NULL;
	temp->cursor = NULL;
	temp->index = -1;
	temp->length = 0;
	return temp;
}

void freeList(List* pL) {
	if ( pL == NULL || *pL == NULL ) {
		return;
	}
	while (length(*pL) != 0) {
		deleteFront(*pL);
	}
	free(*pL);
	*pL = NULL;
}

// Access functions -----------------------------------------------------------
int length(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: length() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return L->length;
}

int index(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: index() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return L->index;
}

int front(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: front() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return L->front->data;
}

int back(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: back() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return L->back->data;
}

int get(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: get() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return L->cursor->data;
}

int equals(List A, List B) {
	if (A == NULL){
		fprintf(stderr, "List Error: equals() called on NULL List A reference\n");
		exit(EXIT_FAILURE);
	}

	if (B == NULL){
		fprintf(stderr, "List Error: equals() called on NULL List B reference\n");
		exit(EXIT_FAILURE);
	}

	Node p = A->front;
	Node q = B->front;

	if(A->length != B->length)
		return 0;
	for(int i = 0; i < A->length; i++){
		if (p->data != q->data)
			return 0;
		p = p->next;
		q = q->next;
	}
	return 1;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: clear() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	freeList(&L);
}

void moveFront(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: moveFront() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (L->length != 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: moveBack() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (L->length != 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: movePrev() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (L->cursor != NULL){
		if (L->cursor == L->front){
			L->cursor = NULL;
			L->index = -1;
		}
		else{
			L->cursor = L->cursor->prev;
			L->index--;
		}
	}
}

void moveNext(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: moveNext() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (L->cursor != NULL){
		if (L->cursor == L->back){
			L->cursor = NULL;
			L->index = -1;
		}
		else{
			L->cursor = L->cursor->next;
			L->index++;
		}
	}
}

void prepend(List L, int data) {
	if (L == NULL){
		fprintf(stderr, "List Error: prepend() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	Node N = malloc (sizeof(NodeObj));
	N->data = data;
	N->next = L->front;
	if (L->front != NULL)
		L->front->prev = N;
	if (L->back == NULL)
		L->back = N;
	L->front = N;
	L->length++;
	if (L->cursor != NULL)
		L->index++;
}

void append(List L, int data) {
	if (L == NULL){
		fprintf(stderr, "List Error: append() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	Node N = malloc (sizeof(NodeObj));
	N->data = data;
	N->prev = L->back;
	if (L->back != NULL)
		L->back->next = N;
	if (L->length == 0)
		L->front = N;
	L->back = N;
	L->length++;
}

void insertBefore(List L, int data) {
	if (L == NULL){
		fprintf(stderr, "List Error: insertBefore() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (!(L->length > 0))
		fprintf(stderr, "No Elements in List");
	else if (!(L->index >= 0))
		fprintf(stderr, "No Cursor Identified");
	else {
		if (L->cursor == L->front)
			prepend(L, data);
		else {
			Node N = malloc (sizeof(NodeObj));
			N->data = data;
			N->next = L->cursor;
			N->prev = L->cursor->prev;
			L->cursor->prev->next = N;
			L->cursor->prev = N;
			L->length++;
			L->index++;
		}
	}
}

void insertAfter(List L, int data) {
	if (L == NULL){
		fprintf(stderr, "List Error: insertAfter() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (!(L->length > 0))
		fprintf(stderr, "No Elements in List");
	else if (!(L->index >= 0))
		fprintf(stderr, "No Cursor Identified");
	else {
		if (L->cursor == L->back)
			append(L, data);
		else {
			Node N = malloc (sizeof(NodeObj));
			N->data = data;
			N->next = L->cursor->next;
			N->prev = L->cursor;
			L->cursor->next->prev = N;
			L->cursor->next = N;
			L->length++;
		}
	}
}

void deleteFront(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: deleteFront() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (!(L->length > 0))
		fprintf(stderr, "No Elements in List");
	else{
		Node temp = L->front;
		if (L->length == 1) {
			L->cursor = NULL;
			L->index = -1;
			L->back = NULL;
		}
		if (L->cursor == temp){
			L->cursor = NULL;
			L->index = -1;
		}
		else if (L->index >= 0)
			L->index--;
		L->front = L->front->next;
		freeNode(&temp);
		L->length--;
	}
}

void deleteBack(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: deleteBack() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (!(L->length > 0))
		fprintf(stderr, "No Elements in List");
	else{

		Node temp = L->back;
		if (L->length == 1) {
			L->cursor = NULL;
			L->index = -1;
			L->front = NULL;
			L->back = NULL;
		}
		else if (L->cursor == temp) {
			L->cursor = NULL;
			L->index = -1;
			L->back = L->back->prev;
			L->back->next = NULL;
		}
		else {
			L->back = L->back->prev;
			L->back->next = NULL;
		}
		freeNode(&temp);
		L->length--;
	}
}

void delete(List L){
	if(L == NULL || L->cursor == NULL){
		fprintf(stderr, "List Error: delete() called on NULL List reference\n");
		exit(1);
	}

	if (!(L->length > 0))
		fprintf(stderr, "No Elements in List");
	else if (!(L->index >= 0))
		fprintf(stderr, "No Cursor Identified");
	else {
		if (L->cursor == L->front)
			deleteFront(L);
		else if (L->cursor == L->back)
			deleteBack(L);
		else{
			Node temp = L->cursor;

			L->cursor->prev = L->cursor->next;
			L->cursor->next->prev = L->cursor->prev;
			freeNode(&temp);

			L->cursor = NULL;
			L->index = -1;
			L->length--;
		}
	}
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: printList() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (out == NULL){
		fprintf(stderr, "List Error: printList() called on NULL out reference\n");
		exit(EXIT_FAILURE);
	}

	if (L->front != NULL){
		fprintf(out, "%d", L->front->data);
		Node temp = L->front->next;
		while (temp != NULL){
     		fprintf(out, " %d", temp->data);
			temp = temp->next;
		}
	}
}

List copyList(List L) {
	if (L == NULL){
		fprintf(stderr, "List Error: copyList() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	List clone = newList();
	Node temp = L->front;
	for(int i = 0; i < L->length; i++){
		append(clone, temp->data);
		temp = temp->next;
	}
	return clone;
}