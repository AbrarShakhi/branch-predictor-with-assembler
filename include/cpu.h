#ifndef CPU_H
#define CPU_H

#include "assembler.h"


typedef struct Cpu Cpu;

typedef struct {
	char *key;
	void (*value)(Cpu *, char **);
} OpcodeEntry;

typedef struct Process {
	char ***instructions;
	LabelEntry *labels;
	int instruction_len;
} Process;

typedef struct {
	char *key;
	int *value;
} RegisterEntry;

typedef struct {
	char *key;
	int *value;
} MemoryEntry;


typedef struct Cpu {
	int program_counter;
	char **instruction_register;
	int accumulator;
	OpcodeEntry *opcode_funcmap;
	int *stack;
	RegisterEntry *registers;
	MemoryEntry *memory;
	Process *process;
} Cpu;

Cpu *cpu_create();
void cpu_load_process(Cpu *, char ***, LabelEntry *);
void cpu_interpret(Cpu *);
void cpu_destroy(Cpu *);

#endif