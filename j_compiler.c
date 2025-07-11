#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

bool is_stack_empty(Stack *s) {
	return s->topNodeAddress == NULL;
}

void push_to_stack(Stack *s, const char *str) {

	Node *new_node = malloc(sizeof(Node));
	if (!new_node) {
		fprintf(stderr, "Error: malloc failed\n");
		exit(1);
	}

	new_node->belowNodeAddress = s->topNodeAddress;

	new_node->value = malloc(strlen(str) + 1);
	if (!new_node->value) {
		fprintf(stderr, "Error: malloc failed\n");
		exit(1);
	}

	strcpy(new_node->value, str);
	s->topNodeAddress = new_node;
}

char *pop_from_stack(Stack *s) {

    if (is_stack_empty(s)) {
        fprintf(stderr, "Error: Attempted to pop from empty stack\n");
        exit(1);
    }

	Node *old_top_node_address = s->topNodeAddress;
	char *old_top_node_value_address = old_top_node_address->value;
	s->topNodeAddress = old_top_node_address->belowNodeAddress;
	free(old_top_node_address);
	return old_top_node_value_address;
}

void empty_entire_stack(Stack *s) {
    char *stackValue;
    while ((stackValue = pop_from_stack(s)) != NULL) {
        free(stackValue);
    }
}

void print_and_pop_entire_stack(Stack *s) {
	char *stack_value;
	while(!is_stack_empty(s)) {
		stack_value = pop_from_stack(s);

		if (stack_value)
		    printf("%s\n", stack_value);
		else
		    printf("Stack is empty!\n");

		free(stack_value);
	}
}

void perform_stack_unit_tests() {
    printf("Running stack unit tests...\n");

    Stack *s = initialize_stack();
    if (s == NULL) {
        printf("FAIL: Stack initialization returned NULL\n");
        return;
    }

	//Test: is_stack_empty
	if (is_stack_empty(s))
		printf("PASS: is_stack_empty returned TRUE when stack was empty\n");
	else
		printf("FAIL: is_stack_empty did not return TRUE when stack was empty\n");

    // Test: Pushing elements
    push_to_stack(s, "A");
    push_to_stack(s, "B");
    push_to_stack(s, "C");

	//Test: is_stack_empty
	if (!is_stack_empty(s))
		printf("PASS: is_stack_empty returned FALSE when stack was non-empty\n");
	else
		printf("FAIL: is_stack_empty did not return FALSE when stack was non-empty\n");

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

    free(s);
    printf("All tests complete.\n");
}

char *convert_char_to_string(char ch) {
    char *str = malloc(2);
    if (!str) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    str[0] = ch;
    str[1] = '\0';
    return str;
}

bool is_numeric_string(const char *str) {
    if (str == NULL || *str == '\0') return false;  // empty string

    if (*str == '-') str++;

    while (*str) {
        if (!isdigit(*str)) return false;
        str++;
    }
    return true;
}


int main(int argc, char *argv[]) {


	// perform_stack_unit_tests();

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]); // argv[0] is always reserved for the name of THIS FILE
		return 1; // error return
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error opening file");
	}

	Stack *s = initialize_stack();

	char file_char_read;
	while((file_char_read = fgetc(file)) != EOF) { 
		printf("%c", file_char_read);

		if (file_char_read == ' ') {
			continue;
		} else {
			push_to_stack(s, convert_char_to_string(file_char_read)); // revist when interpreting string literals
		}
		
	}
	
	fclose(file);

	char *stack_read;
	while(!is_stack_empty(s)) {
		stack_read = pop_from_stack(s);
		if (strcmp(stack_read, "+") == 0) {
			char *right_summand = pop_from_stack(s);
			char *left_summand  = pop_from_stack(s);

			if (!is_numeric_string(right_summand) || !is_numeric_string(left_summand)) {
				fprintf(stderr,
					"Error: Invalid sum expression.\n"
					"  Left:  %s\n"
					"  Right: %s\n"
					"  Operator: %s\n",
					left_summand, right_summand, stack_read);

				exit(1);
			}

			printf("%d\n", atoi(left_summand) + atoi(right_summand));
			free(left_summand);
			free(right_summand);

		}

		free(stack_read);
	}

	printf("Program successful, exitting");
	return 0;
}