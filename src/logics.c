#include "logics.h"

#include "cpu.h"
#include "miscs.h"
#include "stb_ds.h"


void add_func(Cpu *cpu, char **operand) {
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
}

void mul_func(Cpu *cpu, char **operand) {
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
}

void sub_func(Cpu *cpu, char **operand) {
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
}

void div_func(Cpu *cpu, char **operand) {
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
}

void push_func(Cpu *cpu, char **operand) {
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
}

void pop_func(Cpu *cpu, char **operand) {
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
}