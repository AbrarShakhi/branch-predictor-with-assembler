#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "stb_ds.h"

Assembler *assembler_create(const char *file) {
	Assembler *assembler = malloc(sizeof(Assembler));
	if (!assembler) {
		unable_to_allocate_memory_error("assembler");
		exit(-1);
	}
	assembler->file = file;
	return assembler;
}

void assembler_parse(Assembler *assembler) {
	assembler->lines = read_assembly(assembler->file);
}

void assembler_tokenize(Assembler *assembler) {
	fprintf(stderr, "NOT IMPLEMENTED YET");
}

void assembler_distroy(Assembler *assembler) {
	if (!assembler) {
		return;
	}
	if (assembler->lines) {
		for (int i = 0; i < arrlen(assembler->lines); i++) {
			if ((assembler->lines)[i]) {
				free((assembler->lines)[i]);
				(assembler->lines)[i] = NULL;
			}
		}
		arrfree(assembler->lines);
	}
	free(assembler);
	assembler = NULL;
}
