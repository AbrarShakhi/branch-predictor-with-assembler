#include "operation.h"

#include <stdio.h>

#include "assembler.h"
#include "cpu.h"
#include "miscs.h"
#include "stb_ds.h"


int add_func(Cpu *cpu, char **operand)
{
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) { segmentation_fault_error("Stack underflow"); }
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
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first + second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[2]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first + second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}

	return -1;
}

int mul_func(Cpu *cpu, char **operand)
{
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) { segmentation_fault_error("Stack underflow"); }
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
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first * second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[2]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first * second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int sub_func(Cpu *cpu, char **operand)
{
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) { segmentation_fault_error("Stack underflow"); }
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
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first - second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[2]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first - second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int div_func(Cpu *cpu, char **operand)
{
	int first, second;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) { segmentation_fault_error("Stack underflow"); }
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
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first / second));
			break;
		case 3:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[2]);
			cpu_set_value_to_mem_or_reg(cpu, operand[0], (first / second));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int push_func(Cpu *cpu, char **operand)
{
	int value;
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 1) { segmentation_fault_error("Stack underflow"); }
			value = cpu->ac;
			arrpush(cpu->stack, value);
			break;
		case 1:
			value = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			arrpush(cpu->stack, value);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}

int pop_func(Cpu *cpu, char **operand)
{
	switch (operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 1) { segmentation_fault_error("Stack underflow"); }
			cpu->ac = arrpop(cpu->stack);
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return -1;
}


int stor_func(Cpu *cpu, char **operand)
{
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

int load_func(Cpu *cpu, char **operand)
{
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

int jmp_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			label_entry = shgetp_null(cpu->process->labels, operand[0]);
			if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
			jump_to = label_entry->value;
			if (!valid_jump(jump_to, cpu->process->instruction_len)) {
				segmentation_fault_error("Invalid jump statement");
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int je_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if (cpu->alu.eq) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int jne_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if (!(cpu->alu.eq)) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int jl_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if (!(cpu->alu.eq) && (cpu->alu.neg)) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int jle_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if ((cpu->alu.eq) || (cpu->alu.neg)) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int jg_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if (!(cpu->alu.eq) && !(cpu->alu.neg)) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int jge_func(Cpu *cpu, char **operand)
{
	int jump_to = -1;
	LabelEntry *label_entry;
	switch (operand_len(operand)) {
		case 1:
			if ((cpu->alu.eq) || !(cpu->alu.neg)) {
				label_entry = shgetp_null(cpu->process->labels, operand[0]);
				if (!label_entry) { segmentation_fault_error("Invalid jump statement"); }
				jump_to = label_entry->value;

				if (!valid_jump(jump_to, cpu->process->instruction_len)) {
					segmentation_fault_error("Invalid jump statement");
				}
			}
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	return jump_to;
}

int cmp_func(Cpu *cpu, char **operand)
{
	int first, second;
	bool eq = false, neg = false;
	switch (operand_len(operand)) {
		case 1:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			eq = (cpu->ac - first) == 0;
			neg = (cpu->ac - first) < 0;
			break;
		case 2:
			first = cpu_get_value_from_mem_or_reg(cpu, operand[0]);
			second = cpu_get_value_from_mem_or_reg(cpu, operand[1]);
			eq = (first - second) == 0;
			neg = (first - second) < 0;
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	cpu->alu.eq = eq;
	cpu->alu.neg = neg;
	return -1;
}

int call_func(Cpu *cpu, char **operand)
{
	fprintf(stdout, "==================PRINT==================\n");
	switch (operand_len(operand)) {
		case 0:
			fprintf(stdout, CYAN "[" YELLOW "%s" CYAN "]: " GREEN "%d\n" RESET, "AC", cpu->ac);
			break;
		case 1:
			fprintf(
			    stdout, CYAN "[" YELLOW "%s" CYAN "]: " GREEN "%d\n" RESET, operand[0],
			    cpu_get_value_from_mem_or_reg(cpu, operand[0]));
			break;
		default:
			invalid_instruction_error(cpu->ir);
	}
	fprintf(stdout, "=========================================\n");
	return -1;
}