#ifndef CPU_H
#define CPU_H

#include <stdio.h>

#include "assembler.h"
#include "predictor.h"

typedef struct Cpu Cpu;

typedef struct OpcodeEntry {
  char *key;
  int (*value)(Cpu *, char **);
} OpcodeEntry;

typedef struct Process {
  char ***instructions;
  LabelEntry *labels;
  int instruction_len;
} Process;

typedef struct MemoryEntry {
  char *key;
  char *value;
} MemoryEntry;

typedef struct Alu {
  bool eq;
  bool neg;
} Alu;

typedef struct Cpu {
  int pc;
  int mar;
  char **ir;
  int ac;
  Alu alu;
  OpcodeEntry *opcode_funcmap;
  int *stack;
  MemoryEntry *memory;
  Process *process;
  Predictor *predictor;
} Cpu;

/**
 * Maps opcode mnemonics to their corresponding handler functions.
 *
 * Initializes and returns a hashmap where keys are opcode strings (e.g., "ADD",
 * "JMP") and values are pointers to the corresponding implementation functions.
 * The "NOP" opcode is mapped to NULL as it requires no operation.
 *
 * @return A hashmap mapping opcode strings to their handler functions.
 */
OpcodeEntry *map_opcode_logics();

/**
 * Returns the length (number of tokens) in a NULL-terminated array of operand
 * strings.
 *
 * @param operand NULL-terminated array of operand strings.
 * @return The count of operand tokens in the array. Returns 0 if operand is
 * NULL.
 */
int operand_len(char **operand);

/**
 * Checks whether a jump destination is valid within the range of instructions.
 *
 * Valid destinations are those between 0 and `ilen`, inclusive.
 *
 * @param dest The jump destination index.
 * @param ilen The total number of instructions.
 * @return true if `dest` is within bounds, false otherwise.
 */
bool valid_jump(int dest, int ilen);

/**
 * Creates and initializes a new Cpu instance.
 *
 * Allocates memory for the Cpu structure, sets up the opcode-function map,
 * and creates a branch predictor with a threshold of 8.
 *
 * @return A pointer to the newly allocated and initialized Cpu instance.
 * @throws Calls unable_to_allocate_memory_error if memory allocation fails.
 */
Cpu *cpu_create();

/**
 * Retrieves the integer value from a given operand, which can be:
 * - A numeric constant (digits only).
 * - The AC register ("AX").
 * - The top value on the stack ("STK").
 * - A memory location specified by braces (e.g., "(address)").
 *
 * If the operand does not match any of the above, attempts to access it as a
 * memory address. If the memory address is not found, triggers a segmentation
 * fault error.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param operand The operand string representing a register, a number, or
 * memory address.
 * @return The integer value corresponding to the operand.
 * @throws Calls segmentation_fault_error on stack underflow or memory access
 * violation.
 */
int cpu_get_value_from_mem_or_reg(Cpu *cpu, char *operand);

/**
 * Sets the value of a register or memory location specified by the operand.
 *
 * Handles:
 * - Setting the AC register if operand is "AC".
 * - Setting a memory location indicated by braces (e.g., "(address)").
 * - If the memory location does not exist, creates a new entry with the given
 * value.
 *
 * Memory values are stored as dynamically allocated strings; old values are
 * freed.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param operand The operand string specifying a register or memory address.
 * @param value The integer value to set.
 */
void cpu_set_value_to_mem_or_reg(Cpu *cpu, char *operand, int value);

/**
 * Loads a process consisting of instructions and labels into the CPU.
 *
 * Initializes the program counter to zero and allocates memory for the Process
 * structure, then associates the given instructions and labels with the CPU's
 * current process. Also sets the instruction count based on the number of
 * instructions.
 *
 * @param cpu Pointer to the Cpu instance to load the process into.
 * @param instructions A NULL-terminated array of tokenized instruction lines.
 * @param labels A hash map of label entries for jump targets.
 * @throws Calls unable_to_allocate_memory_error if memory allocation for
 * Process fails.
 */
void cpu_load_process(Cpu *cpu, char ***instructions, LabelEntry *labels);
/**
 * Checks whether the CPU has finished processing all instructions.
 *
 * Compares the program counter (pc) to the total instruction length.
 *
 * @param cpu Pointer to the Cpu instance.
 * @return true if the pc is greater than or equal to the instruction count,
 * false otherwise.
 */
bool __cpu_process_finish(Cpu *cpu);

/**
 * Fetches the instruction at the given index from the CPU's loaded process.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param i Index of the instruction to fetch.
 * @return The tokenized instruction at index `i`.
 */
char **__cpu_fetch_instruction(Cpu *cpu, int i);

/**
 * Decodes an instruction by looking up its opcode in the CPU's opcode-function
 * map.
 *
 * Sets the `is_jump` flag to true if the opcode starts with 'J' (indicating a
 * jump). Calls invalid_instruction_error if the opcode is not recognized.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param instruction The tokenized instruction.
 * @param is_jump Pointer to a boolean flag set to true if the instruction is a
 * jump, else false.
 * @return Pointer to the OpcodeEntry function handler for the opcode.
 */
OpcodeEntry *__cpu_decode_instruction(Cpu *cpu, char **instruction,
                                      bool *is_jump);

/**
 * Extracts operands from the current instruction register (ir) of the CPU.
 *
 * Copies all tokens except the first one (opcode) into a newly allocated
 * operand array.
 *
 * @param cpu Pointer to the Cpu instance.
 * @return A NULL-terminated array of operand tokens.
 * @throws Calls invalid_instruction_error if there are no tokens in the
 * instruction.
 */
char **__cpu_fetch_operand(Cpu *cpu);
/**
 * Executes a CPU instruction by calling the mapped opcode function.
 *
 * Frees the dynamically allocated operand array after execution.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param opcode_map Pointer to the OpcodeEntry containing the function to
 * execute.
 * @param operand NULL-terminated array of operand tokens.
 * @return The index of the next instruction to execute, or -1 for default
 * sequential execution.
 */
int __cpu_execute_instruction(Cpu *cpu, OpcodeEntry *opcode_map,
                              char **operand);

/**
 * Prints the current CPU and branch predictor state for debugging.
 *
 * Displays program counter (PC), memory address register (MAR), instruction
 * register (IR), ALU flags (equal and negative), accumulator (AC) value,
 * predicted and actual branch outcomes, and predictor counter value for the
 * current instruction.
 *
 * @param cpu Pointer to the Cpu instance.
 * @param predictor Pointer to the Predictor instance.
 * @param predicted_taken Boolean indicating the predicted branch outcome.
 * @param actual_taken Boolean indicating the actual branch outcome.
 */
void print_cpu_debug_state(Cpu *cpu, Predictor *predictor, bool predicted_taken,
                           bool actual_taken);

/**
 * Executes the loaded process on the CPU by interpreting instructions
 * sequentially.
 *
 * The function fetches, decodes, and executes each instruction while managing
 * program flow:
 * - Updates program counter (PC) and memory address register (MAR).
 * - Predicts branch outcomes and tracks actual jumps.
 * - Updates the branch predictor based on actual vs predicted outcomes.
 * - Prints CPU state after each instruction.
 * - Waits for a key press before continuing to the next instruction.
 *
 * Execution ends when all instructions in the process have been processed.
 *
 * @param cpu Pointer to the Cpu instance running the interpretation.
 */
void cpu_interpret(Cpu *cpu);

/**
 * Frees all resources associated with the given Cpu instance.
 *
 * This includes:
 * - Destroying the branch predictor.
 * - Freeing all dynamically allocated memory entries in the CPU memory hashmap.
 * - Freeing the CPU stack array.
 * - Freeing the loaded process structure.
 * - Freeing the opcode-function map.
 * - Finally, freeing the Cpu structure itself.
 *
 * Safely handles a NULL cpu pointer by doing nothing.
 *
 * @param cpu Pointer to the Cpu instance to destroy.
 */
void cpu_destroy(Cpu *cpu);

#endif