#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "stb_ds.h"


void missing_filename_error() {
	fprintf(stderr, "File name required!\n");
	fprintf(stderr, "Use Case:\n");
	fprintf(stderr, "\t[myprogram] -i [assembly.s]\n");
	exit(-1);
}

void unable_to_allocate_memory_error(const char *variable_name) {
	fprintf(stderr, "Unable to allocate memory [%s]", variable_name);
	exit(-1);
}

void free_and_null(void *ptr) {
	free(ptr);
	ptr = NULL;
}

void unrecognized_assembly_syntax_error(const char *line, int line_number) {
	fprintf(stderr, "unrecognized assembly syntax.\n");
	fprintf(stderr, "line number: %d\n", line_number);
	fprintf(stderr, ">> %s\n", line);
	exit(-1);
}

void invalid_instruction_error(char **instruction) {
	fprintf(stderr, "\n");
	for (int i = 0; i < arrlen(instruction); i++) {
		fprintf(stderr, "%s ", instruction[i]);
	}
	fprintf(stderr, "\n__^^^__ Bad instructions.\n");
	exit(-1);
}

void segmentation_fault_error(const char *error_msg) {
	fprintf(stderr, "Segmentation fault occured: %s\n", error_msg);
	exit(-1);
}


void could_not_open_file(const char *file) {
	fprintf(stderr, "Could not open: %s\n", file);
	exit(-1);
}

void unknown_opcode_error(char **instruction, const char *alt) {
	fprintf(stderr, "\n");
	for (int i = 0; i < arrlen(instruction); i++) {
		fprintf(stderr, "%s ", instruction[i]);
	}
	fprintf(stderr, "\n__^^^__ Unrecognized opcode.\n");
	if (alt) {
		fprintf(stderr, "Did you mean: %s\n", alt);
	}
	exit(-1);
}