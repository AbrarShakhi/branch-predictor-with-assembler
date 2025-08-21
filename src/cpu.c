#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "bool.h"
#include "reader.h"
#include "stb_ds.h"


Cpu *cpu_create() {
	Cpu *cpu = (Cpu *)malloc(sizeof(Cpu));
	if (!cpu) {
		unable_to_allocate_memory_error("cpu");
		exit(-1);
	}
	cpu->program_counter = 0;
	cpu->instruction_register = NULL;
	cpu->accumulator = 0;
	cpu->process = NULL;
	return cpu;
}

void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels) {
	cpu->program_counter = 0;
	cpu->process = (Process *)malloc(sizeof(Process));
	if (!cpu->process) {
		unable_to_allocate_memory_error("cpu");
		exit(-1);
	}
	cpu->process->instructions = instructions;
	cpu->process->labels = labels;
	cpu->process->instruction_len = arrlen(cpu->process->instructions);
}

bool __cpu_process_finish(Cpu *cpu) {
	return (cpu->program_counter >= cpu->process->instruction_len);
}

void __cpu_execute_instruction(Cpu *cpu) {
	for (int i = 0; i < arrlen(cpu->instruction_register); i++) {
		printf("%s ", cpu->instruction_register[i]);
	}
	printf("\n");
}


void cpu_interpret(Cpu *cpu) {
	while (true) {
		if (__cpu_process_finish(cpu)) {
			break;
		}
		cpu->instruction_register =
		    cpu->process->instructions[cpu->program_counter];
		(cpu->program_counter)++;

		__cpu_execute_instruction(cpu);
	}
}

void cpu_destroy(Cpu *cpu) {
	if (!cpu) {
		return;
	}
	if (cpu->process) {
		free_and_null(cpu->process);
	}
	free_and_null(cpu);
}