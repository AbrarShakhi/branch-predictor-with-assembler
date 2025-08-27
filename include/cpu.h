#ifndef CPU_H
#define CPU_H

#include <stdio.h>

#include "assembler.h"
#include "predictor.h"

typedef struct Cpu Cpu;

typedef struct {
  char *key;
  int (*value)(Cpu *, char **);
} OpcodeEntry;

typedef struct Process {
  char ***instructions;
  LabelEntry *labels;
  int instruction_len;
} Process;

typedef struct {
  char *key;
  char *value;
} MemoryEntry;

typedef struct Alu {
  bool eq;
  bool neg;
} Alu;

typedef struct Cpu {
  int pc;
  int mar;
  char **ir;
  int ac;
  Alu alu;
  OpcodeEntry *opcode_funcmap;
  int *stack;
  MemoryEntry *memory;
  Process *process;
  Predictor *predictor;
} Cpu;

OpcodeEntry *map_opcode_logics();
int operand_len(char **);

Cpu *cpu_create();
int cpu_get_value_from_mem_or_reg(Cpu *, char *);
void cpu_set_value_to_mem_or_reg(Cpu *, char *, int);
void cpu_load_process(Cpu *, char ***, LabelEntry *);
void cpu_interpret(Cpu *);
void cpu_destroy(Cpu *);

#endif