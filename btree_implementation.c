#include <stdio.h>

#define MAX_NUMBER_OF_KEYS 1

typedef struct Node {
	struct Node* childNodes[MAX_NUMBER_OF_KEYS + 1];
	int keys[MAX_NUMBER_OF_KEYS];
} Node;

typedef struct Btree {
	Node* rootNodeAddress;
} Btree;

Btree* initialize_btree(int rootNodeKey) {

	*Node n;
	n->childNodes = NULL;
	n->keys = {rootNodeKey};

	*Btree b;
	b->rootNodeAddress = n;

	return b;
}

int main() {

	Btree* b = initialize_btree(5);

	return 0;
}