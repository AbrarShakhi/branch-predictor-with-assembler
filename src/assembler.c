#include "assembler.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miscs.h"
#include "parse_str.h"
#include "reader.h"
#include "stb_ds.h"


Assembler *assembler_create(const char *file) {
	Assembler *assembler = (Assembler *)calloc(1, sizeof(Assembler));
	if (!assembler) {
		unable_to_allocate_memory_error("assembler");
	}
	assembler->file = file;
	return assembler;
}

void assembler_parse(Assembler *assembler) {
	assembler->lines = read_assembly(assembler->file);
}

char **preprocess(char *line) {
	if (is_line_empty_or_whitespace(line)) {
		NULL;
	}
	trim_whitespace_inplace(line);

	char **tokens = NULL;
	char *token = strtok(line, " \t");
	while (token != NULL) {
		remove_trailing_char(token, ',');
		arrpush(tokens, token);
		token = strtok(NULL, " \t");
	}

	return tokens;
}

bool is_label(char **tokens) {
	int token_len = arrlen(tokens);
	if (token_len == 1) {
		return ends_with(tokens[0], ':');
	}
	return false;
}

void assembler_tokenize(Assembler *assembler) {
	int line_length = arrlen(assembler->lines);

	int instruction_id = 0;
	for (int i = 0; i < line_length; i++) {
		char *line = assembler->lines[i];

		char **tokens = preprocess(line);
		if (!tokens) {
			continue;
		}

		if (is_label(tokens)) {
			remove_trailing_char(tokens[0], ':');
			remove_leading_char(tokens[0], '.');
			shput(assembler->labels, tokens[0], instruction_id);
		} else if (!starts_with(tokens[0], '.')) {
			arrpush(assembler->instructions, tokens);
			instruction_id++;
		}
	}
}

void assembler_destroy(Assembler *assembler) {
	if (!assembler) {
		return;
	}
	if (assembler->instructions) {
		for (int i = 0; i < arrlen(assembler->instructions); i++) {
			arrfree(assembler->instructions[i]);
		}
		arrfree(assembler->instructions);
	}
	if (assembler->labels) {
		shfree(assembler->labels);
	}
	if (assembler->lines) {
		for (int i = 0; i < arrlen(assembler->lines); i++) {
			free_and_null(assembler->lines[i]);
		}
		arrfree(assembler->lines);
	}
	free_and_null(assembler);
}
