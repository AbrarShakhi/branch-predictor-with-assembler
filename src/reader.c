#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stb_ds.h"

void unable_to_allocate_memory_error(char *variable_name) {
	fprintf(stderr, "Unable to allocate memory [%s]", variable_name);
}


char *read_line(FILE *stream) {
	size_t capacity = 128;
	size_t length = 0;
	char *buffer = malloc(capacity);
	if (!buffer)
		return NULL;

	int c;
	while ((c = fgetc(stream)) != EOF) {
		if (c == '\n')
			break;
		buffer[length++] = (char)c;
		if (length + 1 >= capacity) {
			capacity *= 2;
			char *tmp = realloc(buffer, capacity);
			if (!tmp) {
				free(buffer);
				return NULL;
			}
			buffer = tmp;
		}
	}

	if (c == EOF && length == 0) {
		free(buffer);
		return NULL;
	}

	buffer[length] = '\0';
	return buffer;
}

char **read_assembly(const char *file) {
	FILE *in = fopen(file, "r");
	if (!in) {
		fprintf(stderr, "Could not open: %s\n", file);
		exit(-1);
	}

	char **lines = NULL;
	char *line;

	while ((line = read_line(in)) != NULL) {
		arrput(lines, line);
	}

	fclose(in);
	return lines;
}