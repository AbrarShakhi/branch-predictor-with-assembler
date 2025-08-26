#include "logics.h"

#include "cpu.h"
#include "miscs.h"
#include "stb_ds.h"


int add_func(Cpu *cpu, char **operand) {
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			first = arrpop(cpu->stack);
			second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second + first));
			break;
		case 1:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			cpu->ac = cpu->ac + first;
			break;
		case 2:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[1], (first + second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[2], (first + second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}

	return -1;
}

int mul_func(Cpu *cpu, char **operand) {
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			first = arrpop(cpu->stack);
			second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second * first));
			break;
		case 1:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			cpu->ac = cpu->ac * first;
			break;
		case 2:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[1], (first * second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[2], (first * second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int sub_func(Cpu *cpu, char **operand) {
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			first = arrpop(cpu->stack);
			second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second - first));
			break;
		case 1:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			cpu->ac = cpu->ac - first;
			break;
		case 2:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[1], (first - second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[2], (first - second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int div_func(Cpu *cpu, char **operand) {
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			first = arrpop(cpu->stack);
			second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second / first));
			break;
		case 1:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			cpu->ac = cpu->ac / first;
			break;
		case 2:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[1], (first / second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[2], (first / second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int push_func(Cpu *cpu, char **operand) {
	int value;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 1) {
				segmentation_fault_error("Stack underflow");
			}
			value = cpu->ac;
			break;
		case 1:
			value = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	arrpush(cpu->stack, value);
	return -1;
}

int pop_func(Cpu *cpu, char **operand) {
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 1) {
				segmentation_fault_error("Stack underflow");
			}
			cpu->ac = arrpop(cpu->stack);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}


int stor_func(Cpu *cpu, char **operand) {
	int value;
	switch (operand_len(operand)) {
		case 1:
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (cpu->ac));
			break;
		case 2:
			value = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], value);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int load_func(Cpu *cpu, char **operand) {
	int value;
	switch (operand_len(operand)) {
		case 1:
			value = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			cpu->ac = value;
			break;
		case 2:
			value = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], value);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}
