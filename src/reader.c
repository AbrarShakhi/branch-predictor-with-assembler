#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miscs.h"
#include "stb_ds.h"

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
        free_and_null(buffer);
        return NULL;
      }
      buffer = tmp;
    }
  }

  if (c == EOF && length == 0) {
    free_and_null(buffer);
    return NULL;
  }

  buffer[length] = '\0';
  return buffer;
}

char **read_assembly(const char *file) {
  FILE *in = fopen(file, "r");
  if (!in) {
    could_not_open_file(file);
  }

  char **lines = NULL;
  char *line;

  while ((line = read_line(in)) != NULL) {
    arrpush(lines, line);
  }

  fclose(in);
  return lines;
}