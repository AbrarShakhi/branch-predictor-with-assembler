#define STB_DS_IMPLEMENTATION


#include "args.h"
#include "assembler.h"
#include "cpu.h"
#include "miscs.h"


Assembler *assembler;
Cpu *cpu;

int main(const int argc, char *argv[]) {
	// char *input_file = parse_args(argc, argv);
	// if (!input_file) { missing_filename_error(*argv); }
	char *input_file = "/home/abrarshakhi/Desktop/branch-predictor-with-assembler/example/ifelse.s";

	assembler = assembler_create(input_file);
	assembler_parse(assembler);
	assembler_tokenize(assembler);

	cpu = cpu_create();
	cpu_load_process(cpu, assembler->instructions, assembler->labels);
	cpu_interpret(cpu);

	clean_up();
	return 0;
}
