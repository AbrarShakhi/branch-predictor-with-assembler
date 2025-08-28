#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "stb_ds.h"

typedef struct LabelEntry{
  char *key;
  int value;
} LabelEntry;

typedef struct Assembler {
  char **lines;
  char *file;
  char ***instructions;
  LabelEntry *labels;
} Assembler;

Assembler *assembler_create(char *);

void assembler_parse(Assembler *assembler);

void assembler_tokenize(Assembler *assembler);

void assembler_destroy(Assembler *assembler);
#endif