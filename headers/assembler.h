#ifndef ASSEMBLER_H
#define ASSEMBLER_H

typedef struct Assembler {
	char **lines;
	const char *file;
} Assembler;


Assembler *assembler_create(const char *);

void assembler_parse(Assembler *assembler);

void assembler_tokenize(Assembler *assembler);

void assembler_distroy(Assembler *assembler);
#endif