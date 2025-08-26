#include "cpu.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logics.h"
#include "miscs.h"
#include "parse_str.h"
#include "predictor.h"
#include "stb_ds.h"


OpcodeEntry *map_opcode_logics() {
	OpcodeEntry *opcode_funcmap = NULL;
	shdefault(opcode_funcmap, NULL);

	shput(opcode_funcmap, "NOP", NULL);
	shput(opcode_funcmap, "ADD", add_func);
	shput(opcode_funcmap, "SUB", sub_func);
	shput(opcode_funcmap, "MUL", mul_func);
	shput(opcode_funcmap, "DIV", div_func);
	shput(opcode_funcmap, "STOR", stor_func);
	shput(opcode_funcmap, "LOAD", load_func);
	shput(opcode_funcmap, "PUSH", push_func);
	shput(opcode_funcmap, "POP", pop_func);
	// shput(opcode_funcmap, "JMP", JMP_func);

	return opcode_funcmap;
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
	cpu->predictor = predictor_create(8);
	return cpu;
}

int cpu_get_value_from_mem_or_reg(Cpu *cpu, char *operand) {
	if (is_digits_only(operand)) {
		return atoi(operand);
	}
	if (strncmp(operand, "AX", 2)) {
		return cpu->ac;
	}

	if (surrounded_by_braces(operand, '(')) {
		remove_leading_char(operand, '(');
		remove_trailing_char(operand, ')');
		trim_whitespace_inplace(operand);
	}
	MemoryEntry *mem = shgetp_null(cpu->memory, operand);
	if (!mem) {
		segmentation_fault_error("Memory access violation: address not found");
	}
	return atoi(mem->value);
}

void cpu_set_value_to_mem_or_reg(Cpu *cpu, char *operand, int value) {
	if (strncmp(operand, "AC", 2)) {
		cpu->ac = value;
		return;
	}

	if (surrounded_by_braces(operand, '(')) {
		remove_leading_char(operand, '(');
		remove_trailing_char(operand, ')');
		trim_whitespace_inplace(operand);
	}
	MemoryEntry *mem = shgetp_null(cpu->memory, operand);
	if (!mem) {
		shput(cpu->memory, operand, itoa_dynamic(value));
		return;
	}
	free_and_null(mem->value);
	mem->value = itoa_dynamic(value);
}

void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels) {
	cpu->pc = 0;
	cpu->process = (Process *)malloc(1 * sizeof(Process));
	if (!cpu->process) {
		unable_to_allocate_memory_error("cpu");
	}
	cpu->process->instructions = instructions;
	cpu->process->labels = labels;
	cpu->process->instruction_len = arrlen(cpu->process->instructions);
}

bool __cpu_process_finish(Cpu *cpu) {
	return (cpu->pc >= cpu->process->instruction_len);
}

char **__cpu_fetch_instruction(Cpu *cpu, int i) {
	return cpu->process->instructions[i];
}

OpcodeEntry *__cpu_decode_instruction(Cpu *cpu, char **instruction) {
	char *opcode = instruction[0];
	OpcodeEntry *opcode_map = shgetp_null(cpu->opcode_funcmap, opcode);
	if (!opcode_map) {
		invalid_instruction_error(instruction);
	}
	return opcode_map;
}


char **__cpu_fetch_operand(Cpu *cpu) {
	int token_len = arrlen(cpu->ir);
	if (!token_len) {
		invalid_instruction_error(cpu->ir);
	}
	char **operand = NULL;
	for (int i = 1; i < token_len; i++) {
		arrpush(operand, cpu->ir[i]);
	}
	arrpush(operand, NULL);
	return operand;
}

int __cpu_execute_instruction(Cpu *cpu, OpcodeEntry *opcode_map,
                              char **operand) {
	int next_instr = -1;
	if (opcode_map->value) {
		next_instr = (opcode_map->value)(cpu, operand);
	}
	arrfree(operand);
	return next_instr;
}

void cpu_interpret(Cpu *cpu) {
	while (!__cpu_process_finish(cpu)) {
		cpu->mar = cpu->pc;
		cpu->pc++;
		cpu->ir = cpu->process->instructions[cpu->mar];

		bool predicted_taken = predictor_predict(cpu->predictor, cpu->mar);

		int next_instr = __cpu_execute_instruction(
		    cpu,
		    __cpu_decode_instruction(cpu,
		                             __cpu_fetch_instruction(cpu, cpu->mar)),
		    __cpu_fetch_operand(cpu));

		bool actual_taken = (next_instr != -1) && (next_instr != cpu->mar + 1);

		if (predicted_taken == actual_taken) {
			predictor_successful_prediction(cpu->predictor, cpu->mar);
		} else {
			predictor_unsuccessful_prediction(cpu->predictor, cpu->mar);
		}

		if (next_instr != -1) {
			cpu->pc = next_instr;
		}
	}
}

void cpu_print_auc(Cpu *cpu) {
	printf("accumulator: %d\n", cpu->ac);
}

void cpu_destroy(Cpu *cpu) {
	if (!cpu) return;

	if (cpu->predictor) {
		predictor_distroy(cpu->predictor);
		cpu->predictor = NULL;
	}
	if (cpu->memory) {
		for (int i = 0; i < hmlen(cpu->memory); ++i) {
			if (cpu->memory[i].key) {
				free_and_null(cpu->memory[i].key);
			}
			if (cpu->memory[i].value) {
				free_and_null(cpu->memory[i].value);
			}
		}
		hmfree(cpu->memory);
		cpu->memory = NULL;
	}
	if (cpu->stack) {
		arrfree(cpu->stack);
		cpu->stack = NULL;
	}
	if (cpu->process) {
		free_and_null(cpu->process);
	}
	if (cpu->opcode_funcmap) {
		shfree(cpu->opcode_funcmap);
		cpu->opcode_funcmap = NULL;
	}
	free_and_null(cpu);
}
