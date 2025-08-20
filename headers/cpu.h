#ifndef CPU_H
#define CPU_H

#include "assembler.h"


typedef struct Cpu {
	int program_counter;
} Cpu;

Cpu *cpu_create(char ***, LabelEntry *);
void cpu_interpret(Cpu *);
void cpu_destroy(Cpu *);

#endif