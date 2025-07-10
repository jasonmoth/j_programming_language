#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *value;
	struct Node *belowNodeAddress;
} Node;

typedef struct Stack {
	Node *topNodeAddress;
} Stack;

Stack *initialize_stack() {
	Stack *s = malloc(sizeof(Stack));
	s->topNodeAddress = NULL;
	return s;
}

void push_to_stack(Stack *s, const char *str) {

	Node *new_node = malloc(sizeof(Node));
	if (!new_node) {
		fprintf(stderr, "Error: malloc failed!\n");
	exit(1);
	}

	new_node->belowNodeAddress = s->topNodeAddress;

	new_node->value = malloc(strlen(str) + 1);
	if (!new_node->value) {
		fprintf(stderr, "Error: malloc failed!\n");
		exit(1);
	}

	strcpy(new_node->value, str);
	s->topNodeAddress = new_node;
}

char *pop_from_stack(Stack *s) {

	if (s->topNodeAddress == NULL) {
		return NULL;
	}

	Node *old_top_node_address = s->topNodeAddress;
	char *old_top_node_value_address = old_top_node_address->value;
	s->topNodeAddress = old_top_node_address->belowNodeAddress;
	free(old_top_node_address);
	return old_top_node_value_address;
}

void empty_stack(Stack *s) {
    char *stackValue;
    while ((stackValue = pop_from_stack(s)) != NULL) {
        free(stackValue);
    }
}

void print_stack(Stack *s) {
	char *stack_value;
	do {
		stack_value = pop_from_stack(s);

		if (stack_value)
		    printf("%s\n", stack_value);
		else
		    printf("Stack is empty!\n");

		free(stack_value);
	} while (stack_value != NULL);
}

void perform_stack_unit_tests() {
    printf("Running stack unit tests...\n");

    Stack *s = initialize_stack();
    if (s == NULL) {
        printf("FAIL: Stack initialization returned NULL\n");
        return;
    }

    // Test: Pushing elements
    push_to_stack(s, "A");
    push_to_stack(s, "B");
    push_to_stack(s, "C");

    // Expected pop order: C, B, A
    char *val;

    val = pop_from_stack(s);
    if (val && strcmp(val, "C") == 0)
        printf("PASS: First pop returned 'C'\n");
    else
        printf("FAIL: First pop expected 'C', got '%s'\n", val ? val : "NULL");
    free(val);

    val = pop_from_stack(s);
    if (val && strcmp(val, "B") == 0)
        printf("PASS: Second pop returned 'B'\n");
    else
        printf("FAIL: Second pop expected 'B', got '%s'\n", val ? val : "NULL");
    free(val);

    val = pop_from_stack(s);
    if (val && strcmp(val, "A") == 0)
        printf("PASS: Third pop returned 'A'\n");
    else
        printf("FAIL: Third pop expected 'A', got '%s'\n", val ? val : "NULL");
    free(val);

    // Stack should now be empty
    val = pop_from_stack(s);
    if (val == NULL)
        printf("PASS: Popping from empty stack returned NULL\n");
    else {
        printf("FAIL: Popping from empty stack expected NULL, got '%s'\n", val);
        free(val);
    }

    free(s);
    printf("All tests complete.\n");
}


int main() {

	perform_stack_unit_tests();
	
	printf("Program successful, exitting");
	return 0;
}