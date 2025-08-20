#define STB_DS_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include <stdio.h>

#include "args.h"
#include "reader.h"
#include "stb_ds.h"


int main(int argc, char *argv[]) {
	int file_index = parse_args(argc, argv);

	if (file_index == -1) {
		missing_filename_error();
		exit(-1);
	}
	char **lines = read_assembly(argv[file_index]);


	for (int i = 0; i < arrlen(lines); i++) {
		free(lines[i]);
		lines[i] = NULL;
	}
	arrfree(lines);
	return 0;
}
