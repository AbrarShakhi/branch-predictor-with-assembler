#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "stb_ds.h"


typedef struct Assembler {
	char **lines;
	const char *file;
	char ***instructions;
	struct {
		char *key;
		int value;
	} *labels;
} Assembler;


void unrecognized_assembly_syntax_error(char *, int);

Assembler *assembler_create(const char *);

void assembler_parse(Assembler *assembler);

void assembler_tokenize(Assembler *assembler);

void assembler_destroy(Assembler *assembler);
#endif