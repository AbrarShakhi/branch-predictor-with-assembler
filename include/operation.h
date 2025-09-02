#ifndef LOGICS_H
#define LOGICS_H

#include "cpu.h"

/**
 * Performs the ADD operation.
 *
 * Supports 0 to 3 operands:
 * - 0 operands: Pops top two values from the stack, pushes their sum.
 * - 1 operand: Adds the operand value to the accumulator (AC).
 * - 2 operands: Adds the second operand to the first operand's storage.
 * - 3 operands: Adds the second and third operands and stores result in first
 * operand.
 *
 * @param cpu The CPU state.
 * @param operand The array of operand strings.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int add_func(Cpu *cpu, char **operand);

/**
 * Performs the MUL operation.
 *
 * Supports 0 to 3 operands with behavior analogous to add_func, but
 * multiplication.
 *
 * @param cpu The CPU state.
 * @param operand The array of operand strings.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int mul_func(Cpu *cpu, char **operand);

/**
 * Performs the SUB operation.
 *
 * Supports 0 to 3 operands similar to add_func, but subtraction.
 *
 * @param cpu The CPU state.
 * @param operand The array of operand strings.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int sub_func(Cpu *cpu, char **operand);

/**
 * Performs the DIV operation.
 *
 * Supports 0 to 3 operands similar to add_func, but division.
 *
 * @param cpu The CPU state.
 * @param operand The array of operand strings.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int div_func(Cpu *cpu, char **operand);

/**
 * Pushes a value onto the stack.
 *
 * - 0 operands: push the accumulator value.
 * - 1 operand: push the value of the operand.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int push_func(Cpu *cpu, char **operand);

/**
 * Pops a value from the stack into the accumulator.
 *
 * Supports 0 operands.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls segmentation_fault_error on stack underflow.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int pop_func(Cpu *cpu, char **operand);

/**
 * Stores a value into memory or register.
 *
 * Supports 1 or 2 operands:
 * - 1 operand: store accumulator value.
 * - 2 operands: store second operand's value into the first operand's location.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int stor_func(Cpu *cpu, char **operand);

/**
 * Loads a value from memory or register.
 *
 * Supports 1 or 2 operands:
 * - 1 operand: load operand's value into accumulator.
 * - 2 operands: move value of second operand into first operand's location.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int load_func(Cpu *cpu, char **operand);

/**
 * Unconditional jump to a label.
 *
 * Supports 1 operand: label name.
 * Returns the instruction index to jump to.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump to.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jmp_func(Cpu *cpu, char **operand);

/**
 * Jump if equal flag is set.
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump to or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int je_func(Cpu *cpu, char **operand);

/**
 * Jump if equal flag is not set.
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump to or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jne_func(Cpu *cpu, char **operand);

/**
 * Jump if less than (negative and not equal flags).
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jl_func(Cpu *cpu, char **operand);

/**
 * Jump if less or equal (negative or equal flags).
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jle_func(Cpu *cpu, char **operand);

/**
 * Jump if greater than (neither negative nor equal flags).
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jg_func(Cpu *cpu, char **operand);

/**
 * Jump if greater or equal (not negative or equal flags).
 *
 * Supports 1 operand: label name.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens (label).
 * @return Instruction index to jump or -1 if condition not met.
 * @throws Calls segmentation_fault_error for invalid jump targets.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int jge_func(Cpu *cpu, char **operand);

/**
 * Compares two values and sets CPU ALU flags accordingly.
 *
 * Supports 1 or 2 operands:
 * - 1 operand: compares accumulator with operand.
 * - 2 operands: compares first operand with second operand.
 *
 * Sets:
 * - cpu->alu.eq: true if equal.
 * - cpu->alu.neg: true if first < second.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int cmp_func(Cpu *cpu, char **operand);

/**
 * Prints CPU register or memory values to standard output.
 *
 * Supports:
 * - 0 operands: prints the accumulator (AC) value.
 * - 1 operand: prints the value of the specified operand.
 *
 * @param cpu The CPU state.
 * @param operand The operand tokens.
 * @return -1 always.
 * @throws Calls invalid_instruction_error on invalid operands.
 */
int call_func(Cpu *cpu, char **operand);

#endif