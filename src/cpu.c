#include "cpu.h"

#include <stdbool.h>
#include <stdlib.h>

#include "logics.h"
#include "stb_ds.h"
#include "utils.h"


Cpu *cpu_create() {
	Cpu *cpu = (Cpu *)calloc(1, sizeof(Cpu));
	if (!cpu) {
		unable_to_allocate_memory_error("cpu");
		exit(-1);
	}
	shput(cpu->opcode_funcmap, "ADD", add_func);
	shput(cpu->opcode_funcmap, "MUL", mul_func);
	shput(cpu->opcode_funcmap, "DIV", div_func);
	shput(cpu->opcode_funcmap, "SUB", sub_func);
	return cpu;
}

void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels) {
	cpu->program_counter = 0;
	cpu->process = (Process *)malloc(1 * sizeof(Process));
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

int __cpu_execute_instruction(Cpu *cpu) {
	return 0;
}

void cpu_interpret(Cpu *cpu) {
	while (true) {
		if (__cpu_process_finish(cpu)) {
			break;
		}
		cpu->instruction_register =
		    cpu->process->instructions[cpu->program_counter];

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