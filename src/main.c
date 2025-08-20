#define STB_DS_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

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

	// cpu_create();

	// cpu_interpret();

	assembler_destroy(assembler);
	return 0;
}
