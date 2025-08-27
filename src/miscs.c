#include "miscs.h"

#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "cpu.h"
#include "stb_ds.h"


void clean_up()
{
	extern Cpu *cpu;
	extern Assembler *assembler;

	cpu_destroy(cpu);
	assembler_destroy(assembler);
}

void shutdown(int status)
{
	clean_up();
	exit(status);
}

void missing_filename_error(const char *programname)
{
	fprintf(stderr, "File name required!\n");
	fprintf(stderr, "Use Case:\n");
	fprintf(stderr, "\t%s [your assembly file]\n\n", programname);
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "\t%s asmbly.s\n\n", programname);

	fprintf(stderr, "If you unsure what assembly code to pass use our own defined\n");
	fprintf(stderr, "\t%s -e %s\n\n", programname, "ifelse.s");
	fprintf(stderr, "you can use other assembly located in example directory.\n");

	shutdown(-1);
}

void unable_to_allocate_memory_error(const char *variable_name)
{
	fprintf(stderr, "Unable to allocate memory [%s]", variable_name);
	shutdown(-1);
}

void free_and_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void unrecognized_assembly_syntax_error(const char *line, int line_number)
{
	fprintf(stderr, "unrecognized assembly syntax.\n");
	fprintf(stderr, "line number: %d\n", line_number);
	fprintf(stderr, ">> %s\n", line);
	shutdown(-1);
}

void invalid_instruction_error(char **instruction)
{
	fprintf(stderr, "\n");
	for (int i = 0; i < arrlen(instruction); i++) {
		fprintf(stderr, "%s ", instruction[i]);
	}
	fprintf(stderr, "\n__^^^__ Bad instructions.\n");
	shutdown(-1);
}

void segmentation_fault_error(const char *error_msg)
{
	fprintf(stderr, "Segmentation fault occured when executing your assembly: %s\n", error_msg);
	shutdown(-1);
}


void could_not_open_file(const char *file)
{
	fprintf(stderr, "Could not open: %s\n", file);
	shutdown(-1);
}

void unknown_opcode_error(char **instruction, const char *alt)
{
	fprintf(stderr, "\n");
	for (int i = 0; i < arrlen(instruction); i++) {
		fprintf(stderr, "%s ", instruction[i]);
	}
	fprintf(stderr, "\n__^^^__ Unrecognized opcode.\n");
	if (alt) { fprintf(stderr, "Did you mean: %s\n", alt); }
	shutdown(-1);
}

void not_implemented_error(const char *file, const int line, const char *msg)
{
	fprintf(stderr, "NOT IMPLEMENTED CODE: \n");
	fprintf(stderr, "FILE: %s\n", file);
	fprintf(stderr, "LINE: %d\n", line);
	if (msg) { fprintf(stderr, "%s\n", msg); }
	shutdown(-1);
}