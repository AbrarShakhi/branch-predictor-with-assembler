#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "stb_ds.h"
#include <stdbool.h>

typedef struct LabelEntry {
  char *key;
  int value;
} LabelEntry;

typedef struct Assembler {
  char **lines;
  char *file;
  char ***instructions;
  LabelEntry *labels;
} Assembler;

/**
 * Creates and initializes a new Assembler instance.
 *
 * Allocates memory for an Assembler structure, initializes its fields,
 * sets its file member to the provided file string, and initializes the
 * labels array using the shdefault function with a default value of -1.
 *
 * @param file A string representing the file to associate with the assembler.
 * @return A pointer to the newly allocated and initialized Assembler.
 * @throws Calls unable_to_allocate_memory_error if memory allocation fails.
 */
Assembler *assembler_create(char *file);

/**
 * Parses the assembly source file associated with the given Assembler instance.
 *
 * Reads all lines from the file specified by `assembler->file` and stores
 * them in the `assembler->lines` array by calling `read_assembly`.
 *
 * @param assembler Pointer to the Assembler instance to parse.
 */
void assembler_parse(Assembler *assembler);

/**
 * Preprocesses a single line of assembly code by removing comments,
 * trimming whitespace, and tokenizing the line into components.
 *
 * Steps performed:
 * - Returns NULL if the line is empty or contains only whitespace.
 * - Removes comments starting from the first semicolon ';'.
 * - Trims leading and trailing whitespace in place.
 * - Splits the line into tokens separated by spaces and tabs.
 * - Removes any trailing commas from tokens.
 * - Returns a dynamically allocated array of token strings (using `arrpush`),
 *   or NULL if the line is empty after preprocessing.
 *
 * Note: The input `line` is modified during processing.
 *
 * @param line The input line to preprocess (will be modified).
 * @return A NULL-terminated dynamically allocated array of tokens,
 *         or NULL if the line is empty or contains only whitespace after
 * preprocessing.
 */
char **__preprocess(char *line);

/**
 * Checks if the given tokens represent a label in assembly code.
 *
 * A label here is defined as a single token that ends with a colon ':'.
 *
 * @param tokens A NULL-terminated array of token strings.
 * @return true if there is exactly one token and it ends with ':', false
 * otherwise.
 */
bool is_label(char **tokens);

/**
 * Tokenizes lines of assembly code stored in the Assembler instance.
 *
 * Processes each line by converting it to uppercase and preprocessing it into
 * tokens.
 * - If the tokens represent a label (single token ending with ':'), registers
 * the with the current instruction ID in the assembler's label map.
 * - If the first token is not a directive (not starting with '.'), the tokens
 * are added to the assembler's instructions list and the instruction ID is
 * incremented.
 *
 * Lines that are empty or contain only comments are skipped.
 *
 * @param assembler Pointer to the Assembler instance containing lines to
 * tokenize.
 */
void assembler_tokenize(Assembler *assembler);

/**
 * Frees all memory associated with the given Assembler instance.
 *
 * This includes:
 * - The dynamically allocated instruction token arrays.
 * - The file path string.
 * - The labels hash map.
 * - The lines read from the source file.
 * - The Assembler structure itself.
 *
 * Safely handles a NULL pointer by doing nothing.
 *
 * @param assembler Pointer to the Assembler instance to destroy.
 */
void assembler_destroy(Assembler *assembler);

#endif