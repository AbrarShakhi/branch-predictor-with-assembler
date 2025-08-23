#include "cpu.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "logics.h"
#include "miscs.h"
#include "stb_ds.h"


OpcodeEntry *map_opcode_logics() {
	OpcodeEntry *opcode_funcmap = NULL;
	shdefault(opcode_funcmap, NULL);

	// shput(opcode_funcmap, "NOP", nop_func);
	shput(opcode_funcmap, "ADD", add_func);
	shput(opcode_funcmap, "SUB", sub_func);
	shput(opcode_funcmap, "MUL", mul_func);
	shput(opcode_funcmap, "DIV", div_func);
	// shput(opcode_funcmap, "AND", and_func);
	// shput(opcode_funcmap, "OR", or_func);
	// shput(opcode_funcmap, "XOR", xor_func);
	// shput(opcode_funcmap, "STOR", str_func);
	// shput(opcode_funcmap, "MOV", mov_func);
	// shput(opcode_funcmap, "PUSH", push_func);
	// shput(opcode_funcmap, "POP", pop_func);
	// shput(opcode_funcmap, "RET", ret_func);
	// shput(opcode_funcmap, "JMP", JMP_func);

	return opcode_funcmap;
}

char **__create_operand(char **tokens, int token_len) {
	char **operand = NULL;
	for (int i = 1; i < token_len; i++) {
		arrpush(operand, tokens[i]);
	}
	arrpush(operand, NULL);
	return operand;
}

int operand_len(char **operand) {
	int i = 0;
	while (operand && operand[i]) {
		i++;
	}
	return i;
}


Cpu *cpu_create() {
	Cpu *cpu = (Cpu *)calloc(1, sizeof(Cpu));
	if (!cpu) {
		unable_to_allocate_memory_error("cpu");
	}
	cpu->opcode_funcmap = map_opcode_logics();
	return cpu;
}

void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels) {
	cpu->program_counter = 0;
	cpu->process = (Process *)malloc(1 * sizeof(Process));
	if (!cpu->process) {
		unable_to_allocate_memory_error("cpu");
	}
	cpu->process->instructions = instructions;
	cpu->process->labels = labels;
	cpu->process->instruction_len = arrlen(cpu->process->instructions);
}

bool __cpu_process_finish(Cpu *cpu) {
	return (cpu->program_counter >= cpu->process->instruction_len);
}

int __cpu_execute_instruction(Cpu *cpu) {
	int token_len = arrlen(cpu->instruction_register);
	if (!token_len) {
		invalid_instruction_error(cpu->instruction_register);
	}

	char *opcode = cpu->instruction_register[0];
	OpcodeEntry *fnptr = shgetp_null(cpu->opcode_funcmap, opcode);
	if (!fnptr) {
		not_implemented_error(__FILE_NAME__, __LINE__,
		                      "__cpu_execute_instruction");
	}

	char **operand = __create_operand(cpu->instruction_register, token_len);
	if (fnptr->value) {
		(fnptr->value)(cpu, operand);
	}

	arrfree(operand);
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