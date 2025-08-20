#define STB_DS_IMPLEMENTATION

#include "args.h"
#include "assembler.h"
#include "cpu.h"


int main(int argc, char *argv[]) {
	int file_index = parse_args(argc, argv);
	if (file_index == -1) {
		missing_filename_error();
		exit(-1);
	}

	Assembler *assembler = assembler_create(argv[file_index]);
	assembler_parse(assembler);

	assembler_tokenize(assembler);

	char ***instructions = assembler->instructions;
	LabelEntry *labels = assembler->labels;

	Cpu *cpu = cpu_create(instructions, labels);

	cpu_interpret(cpu);

	cpu_destroy(cpu);
	assembler_destroy(assembler);
	return 0;
}
