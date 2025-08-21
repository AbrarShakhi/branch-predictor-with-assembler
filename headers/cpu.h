#ifndef CPU_H
#define CPU_H

#include "assembler.h"


typedef struct Process {
	char ***instructions;
	LabelEntry *labels;
	int instruction_len;
} Process;


typedef struct Cpu {
	int program_counter;
	char **instruction_register;
	int accumulator;


	Process *process;
} Cpu;

Cpu *cpu_create();
void cpu_load_process(Cpu *, char ***, LabelEntry *);
void cpu_interpret(Cpu *);
void cpu_destroy(Cpu *);

#endif