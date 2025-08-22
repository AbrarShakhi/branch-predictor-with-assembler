#include "logics.h"

#include "cpu.h"
#include "stb_ds.h"
#include "utils.h"


int __operand_len(char **operand) {
	int i = 0;
	while (operand && operand[i]) {
		i++;
	}
	return i;
}

void cpu_add_func(Cpu *cpu, char **operand) {
	switch (__operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			int first = arrpop(cpu->stack);
			int second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second + first));
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			invalid_instruction_error(cpu->instruction_register);
	}
}

void cpu_mul_func(Cpu *cpu, char **operand) {
	switch (__operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			int first = arrpop(cpu->stack);
			int second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second * first));
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			invalid_instruction_error(cpu->instruction_register);
	}
}

void cpu_sub_func(Cpu *cpu, char **operand) {
	switch (__operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			int first = arrpop(cpu->stack);
			int second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second - first));
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			invalid_instruction_error(cpu->instruction_register);
	}
}

void cpu_div_func(Cpu *cpu, char **operand) {
	switch (__operand_len(operand)) {
		case 0:
			if (arrlen(cpu->stack) < 2) {
				segmentation_fault_error("Stack underflow");
			}
			int first = arrpop(cpu->stack);
			int second = arrpop(cpu->stack);
			arrpush(cpu->stack, (second / first));
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			invalid_instruction_error(cpu->instruction_register);
	}
}
