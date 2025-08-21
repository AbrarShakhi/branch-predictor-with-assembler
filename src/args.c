#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void missing_filename_error() {
	fprintf(stderr, "File name required!\n");
	fprintf(stderr, "Use Case:\n");
	fprintf(stderr, "\t[myprogram] -i [assembly.s]\n");
}

char *parse_args(const int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-i", 2) == 0) {
			if (i + 1 < argc) {
				return argv[i + 1];
			} else {
				missing_filename_error();
				exit(-1);
			}
		}
	}
	return NULL;
}