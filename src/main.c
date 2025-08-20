#define STB_DS_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include <stdio.h>

#include "args.h"
#include "assembler.h"


int main(int argc, char *argv[]) {
	int file_index = parse_args(argc, argv);
	if (file_index == -1) {
		missing_filename_error();
		exit(-1);
	}

	Assembler *assembler = assembler_create(argv[file_index]);
	assembler_parse(assembler);
	assembler_tokenize(assembler);
	for (int i = 0; i < shlen(assembler->labels); i++) {
		char *label = assembler->labels[i].key;
		int instruction_id = assembler->labels[i].value;

		printf("%s -> %d\n", label, instruction_id);
	}
	assembler_destroy(assembler);
	return 0;
}
