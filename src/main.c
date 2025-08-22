#define STB_DS_IMPLEMENTATION

#include "args.h"
#include "assembler.h"
#include "cpu.h"


int main(int argc, char *argv[]) {
	char *input_file = parse_args(argc, argv);

	Assembler *assembler = assembler_create(input_file);
	assembler_parse(assembler);
	assembler_tokenize(assembler);

	Cpu *cpu = cpu_create();
	cpu_load_process(cpu, assembler->instructions, assembler->labels);
	cpu_interpret(cpu);

	cpu_destroy(cpu);
	assembler_destroy(assembler);
	return 0;
}
