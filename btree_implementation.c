#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_OF_KEYS 1

typedef struct Record {
	int key;
	char value[100];
} Record;

typedef struct Node {
	struct Node* childNodes[MAX_NUMBER_OF_KEYS + 1];
	struct Record keys[MAX_NUMBER_OF_KEYS];
} Node;

typedef struct Btree {
	Node* rootNodeAddress;
} Btree;

Btree* initialize_btree() {

	Node* n = malloc(sizeof(Node));
	if (n == NULL) {
		fprintf(stderr, "Error: Failed to malloc Node on btree initialization.\n");
		exit(1);
	}

	Btree* b = malloc(sizeof(Btree));
	if (b == NULL) {
		fprintf(stderr, "Error: Failed to malloc Btree on btree initialization.\n");
		exit(1);
	}

	b->rootNodeAddress = n;

	return b;
}

void insert_record_into_btree(Record r)
{
	printf("Hello");
}

int main() {

	Btree* b = initialize_btree();
	Record r;

	r.key = 5;
	strcpy(r.value, 'Five');

	printf("r.key = %d", r.key);
	printf("r.key = %s", r.value);

	// printf("b->rootNodeAddress = %p\n", b->rootNodeAddress);
	// printf("(b->rootNodeAddress)->keys[0] = %d\n", (b->rootNodeAddress)->keys[0]);

	printf("Program ran sucessfully, exiting...\n");
	return 0;
}