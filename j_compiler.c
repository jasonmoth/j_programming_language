#include<stdio.h>
#include<stdlib.h>

// want the user to run a command like
// `./j_compiler my_file.j`
// and that will have the program execute



int main(int argc, char *argv[]) { // argc = number of args passed (want to) *argv[] is a string (char pointer) array of the args
	
	// make sure only two args were passed, those being the compiler filename and the file to be compiled
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]); // argv[0] is always reserved for the name of THIS FILE
		return 1; // error return
	}
	
	
	FILE *file = fopen(argv[1], "r"); // you should not (maybe can't) deal with files directly; only pointers to files. All standard library functions expect this pointer not the file struct
	if (file == NULL) {
		perror("Error opening file");
	}

	int ch;
	char *stack[];

	while((ch = fgetc(file)) != EOF) {
		putchar(ch);
	}

	fclose(file);

	return 0;
}
