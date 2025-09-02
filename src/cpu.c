#include "cpu.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "miscs.h"
#include "operation.h"
#include "parse_str.h"
#include "predictor.h"
#include "stb_ds.h"


OpcodeEntry *map_opcode_logics()
{
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
  shput(opcode_funcmap, "CMP", cmp_func);
  shput(opcode_funcmap, "JMP", jmp_func);
  shput(opcode_funcmap, "JE", je_func);
  shput(opcode_funcmap, "JNE", jne_func);
  shput(opcode_funcmap, "JL", jl_func);
  shput(opcode_funcmap, "JLE", jle_func);
  shput(opcode_funcmap, "JG", jg_func);
  shput(opcode_funcmap, "JGE", jge_func);
  shput(opcode_funcmap, "CALL", call_func);
  return opcode_funcmap;
}

int operand_len(char **operand)
{
  int i = 0;
  while (operand && operand[i]) {
	i++;
  }
  return i;
}

bool valid_jump(int dest, int ilen)
{
  return dest >= 0 && dest <= ilen;
}

Cpu *cpu_create()
{
  Cpu *cpu = (Cpu *)calloc(1, sizeof(Cpu));
  if (!cpu) { unable_to_allocate_memory_error("cpu"); }
  cpu->opcode_funcmap = map_opcode_logics();
  cpu->predictor = predictor_create(8);
  return cpu;
}

int cpu_get_value_from_mem_or_reg(Cpu *cpu, char *operand)
{
  if (is_digits_only(operand)) { return atoi(operand); }
  if (strncmp(operand, "AX", 2) == 0) { return cpu->ac; }

  if (strncmp(operand, "STK", 2) == 0) {
	if (!arrlen(cpu->stack)) { segmentation_fault_error("Stack Underflow."); }
	int value = (cpu->stack)[arrlen(cpu->stack) - 1];
	return value;
  }

  if (surrounded_by_braces(operand, '(')) {
	remove_leading_char(operand, '(');
	remove_trailing_char(operand, ')');
	trim_whitespace_inplace(operand);
  }
  MemoryEntry *mem = shgetp_null(cpu->memory, operand);
  if (!mem) { segmentation_fault_error("Memory access violation: address not found"); }
  return atoi(mem->value);
}

void cpu_set_value_to_mem_or_reg(Cpu *cpu, char *operand, int value)
{
  if (strncmp(operand, "AC", 2) == 0) {
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

void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels)
{
  cpu->pc = 0;
  cpu->process = (Process *)malloc(1 * sizeof(Process));
  if (!cpu->process) { unable_to_allocate_memory_error("cpu"); }
  cpu->process->instructions = instructions;
  cpu->process->labels = labels;
  cpu->process->instruction_len = arrlen(cpu->process->instructions);
}

bool __cpu_process_finish(Cpu *cpu)
{
  return (cpu->pc >= cpu->process->instruction_len);
}

char **__cpu_fetch_instruction(Cpu *cpu, int i)
{
  return cpu->process->instructions[i];
}

OpcodeEntry *__cpu_decode_instruction(Cpu *cpu, char **instruction, bool *is_jump)
{
  char *opcode = instruction[0];
  OpcodeEntry *opcode_map = shgetp_null(cpu->opcode_funcmap, opcode);
  if (!opcode_map) { invalid_instruction_error(instruction); }
  if (*opcode == 'J') { *is_jump = true; }
  return opcode_map;
}

char **__cpu_fetch_operand(Cpu *cpu)
{
  int token_len = arrlen(cpu->ir);
  if (!token_len) { invalid_instruction_error(cpu->ir); }
  char **operand = NULL;
  for (int i = 1; i < token_len; i++) {
	arrpush(operand, cpu->ir[i]);
  }
  arrpush(operand, NULL);
  return operand;
}

int __cpu_execute_instruction(Cpu *cpu, OpcodeEntry *opcode_map, char **operand)
{
  int next_instr = -1;
  if (opcode_map->value) { next_instr = (opcode_map->value)(cpu, operand); }
  arrfree(operand);
  return next_instr;
}

void print_cpu_debug_state(Cpu *cpu, Predictor *predictor, bool predicted_taken, bool actual_taken)
{
  fprintf(stdout, MAGENTA BOLD "=== CPU STATE ===" RESET "\n");
  fprintf(
      stdout,
      CYAN "PC: " RESET GREEN "%d" RESET "  " CYAN "MAR: " RESET GREEN "%d" RESET "  " CYAN
           "IR: " RESET YELLOW "\"",
      cpu->pc, cpu->mar);

  for (int i = 0; i < arrlen(cpu->ir); i++) {
	fprintf(stdout, "%s", cpu->ir[i]);
	if (i < arrlen(cpu->ir) - 1) { fprintf(stdout, " "); }
  }
  fprintf(stdout, "\"" RESET "\n");


  fprintf(
      stdout,
      CYAN "ALU EG: " RESET GREEN "%d" RESET "  " CYAN "ALU NEG: " RESET GREEN "%d" RESET "  " CYAN
           "AC: " RESET YELLOW "%d" RESET "\n",
      cpu->alu.eq, cpu->alu.neg, cpu->ac);

  fprintf(
      stdout, BLUE "Predicted: " RESET "%s" RESET "  ",
      predicted_taken ? GREEN "TAKEN" : RED "NOT TAKEN");

  fprintf(stdout, BLUE "Actual: " RESET "%s" RESET, actual_taken ? GREEN "TAKEN" : RED "NOT TAKEN");

  if (predicted_taken == actual_taken) {
	fprintf(stdout, "  " GREEN BOLD "✓ CORRECT" RESET "\n");
  } else {
	fprintf(stdout, "  " RED BOLD "✗ WRONG" RESET "\n");
  }

  CounterEntry *entry = hmgetp_null((predictor->counter_entry), cpu->mar);
  if (entry && entry->value) {
	fprintf(
	    stdout, YELLOW "Predictor Counter [instr %d]: " RESET CYAN "%d\n" RESET, cpu->mar,
	    entry->value->counter);
  } else {
	fprintf(stdout, YELLOW "Predictor Counter [instr %d]: " RESET RED "N/A\n" RESET, cpu->mar);
  }

  fprintf(stdout, WHITE DIM "────────────────────────────────────────\n" RESET);
}


void cpu_interpret(Cpu *cpu)
{
  while (!__cpu_process_finish(cpu)) {
	cpu->mar = cpu->pc;
	cpu->pc++;
	cpu->ir = cpu->process->instructions[cpu->mar];

	bool predicted_taken = predictor_predict(cpu->predictor, cpu->mar);
	bool is_jump = false;
	int next_instr = __cpu_execute_instruction(
	    cpu, __cpu_decode_instruction(cpu, __cpu_fetch_instruction(cpu, cpu->mar), &is_jump),
	    __cpu_fetch_operand(cpu));

	bool actual_taken = (next_instr != -1) && (next_instr != cpu->pc);

	print_cpu_debug_state(cpu, cpu->predictor, predicted_taken, actual_taken);

	if (is_jump) {
	  if (actual_taken) {
		predictor_learn_to_take(cpu->predictor, cpu->mar);
	  } else {
		predictor_learn_not_to_take(cpu->predictor, cpu->mar);
	  }
	}

	if (next_instr != -1) { cpu->pc = next_instr; }

	my_getch();
  }
}

void cpu_destroy(Cpu *cpu)
{
  if (!cpu) { return; }

  if (cpu->predictor) {
	predictor_destroy(cpu->predictor);
	cpu->predictor = NULL;
  }
  if (cpu->memory) {
	for (int i = 0; i < shlen(cpu->memory); ++i) {
	  free_and_null(cpu->memory[i].value);
	}
	shfree(cpu->memory);
  }
  if (cpu->stack) { arrfree(cpu->stack); }
  free_and_null(cpu->process);
  if (cpu->opcode_funcmap) { shfree(cpu->opcode_funcmap); }
  free_and_null(cpu);
}
