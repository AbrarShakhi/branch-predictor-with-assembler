#include "args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miscs.h"
#include "parse_str.h"


char *parse_args(const int argc, char *argv[])
{
  if (argc < 2) { missing_filename_error(argv[0]); }

  size_t len;
  char *filepath = NULL;
  if (starts_with(argv[1], '-')) {
	if (strncmp(argv[1], "-e", 2) == 0 && argc > 2) {
	  len = strlen("./example/") + strlen(argv[2]) + 1;
	  filepath = (char *)malloc(len);
	  if (!filepath) { unable_to_allocate_memory_error("parse_args"); }
	  strcpy(filepath, "./example/");
	  strcat(filepath, argv[2]);
	} else {
	  missing_filename_error(argv[0]);
	}
  } else {
	len = strlen(argv[1]) + 1;
	filepath = (char *)malloc(len);
	if (!filepath) { unable_to_allocate_memory_error("parse_args"); }
	strcpy(filepath, argv[1]);
  }
  return filepath;
}
