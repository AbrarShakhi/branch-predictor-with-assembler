#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "parse_str.h"
#include "reader.h"
#include "stb_ds.h"


void unrecognized_assembly_syntax_error(char *line, int line_number) {
	fprintf(stderr, "unrecognized assembly syntax.\n");
	fprintf(stderr, "line number: %d\n", line_number);
	fprintf(stderr, ">> %s\n", line);
}

Assembler *assembler_create(const char *file) {
	Assembler *assembler = malloc(sizeof(Assembler));
	if (!assembler) {
		unable_to_allocate_memory_error("assembler");
		exit(-1);
	}
	assembler->file = file;
	assembler->lines = NULL;
	assembler->instructions = NULL;
	assembler->labels = NULL;
	return assembler;
}

void assembler_parse(Assembler *assembler) {
	assembler->lines = read_assembly(assembler->file);
}

void assembler_tokenize(Assembler *assembler) {
	int line_length = arrlen(assembler->lines);

	int instruction_id = 0;
	for (int i = 0; i < line_length; i++) {
		char *line = assembler->lines[i];

		if (is_line_empty_or_whitespace(line)) {
			continue;
		}
		trim_whitespace_inplace(line);


		char **tokens = NULL;
		char *token = strtok(line, " \t");
		while (token != NULL) {
			remove_trailing_char(token, ',');
			arrpush(tokens, token);
			token = strtok(NULL, " \t");
		}
		bool is_label = false;
		int token_len = arrlen(tokens);
		if (token_len == 1) {
			if (find_char(tokens[0], ':')) {
				is_label = true;
				remove_trailing_char(tokens[0], ':');
			}
		}

		if (is_label) {
			shput(assembler->labels, tokens[0], instruction_id);
		} else {
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
