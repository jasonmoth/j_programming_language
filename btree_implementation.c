#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_KEYS 1

typedef struct Node {
	struct Node* childNodes[MAX_NUMBER_OF_KEYS + 1];
	int keys[MAX_NUMBER_OF_KEYS];
} Node;

typedef struct Btree {
	Node* rootNodeAddress;
} Btree;

Btree* initialize_btree(int rootNodeKey) {

	Node* n = malloc(sizeof(Node));
	if (n == NULL) {
		fprintf(stderr, "Error: Failed to malloc Node on btree initialization.\n");
		exit(1);
	}
	n->keys[0] = rootNodeKey;

	Btree* b = malloc(sizeof(Btree));
	if (n == NULL) {
		fprintf(stderr, "Error: Failed to malloc Btree on btree initialization.\n");
		exit(1);
	}

	b->rootNodeAddress = n;

	return b;
}

int main() {

	Btree* b = initialize_btree(5);
	printf("b->rootNodeAddress = %p\n(b->rootNodeAddress)->keys[0] = %d\n", b->rootNodeAddress, (b->rootNodeAddress)->keys[0]);
	return 0;
}