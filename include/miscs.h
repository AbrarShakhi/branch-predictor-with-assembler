#ifndef UTILS_H
#define UTILS_H


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"


/**
 * Reads a single character from the keyboard without waiting for a newline.
 *
 * Provides platform-independent functionality: uses _getch() on Windows,
 * and termios-based raw mode on Unix-like systems.
 *
 * @return The character read as an int.
 */
int my_getch();

/**
 * Cleans up resources by destroying the global Cpu and Assembler instances.
 *
 * Calls their respective destroy functions and frees associated memory.
 * Expects `cpu` and `assembler` to be defined as external global pointers.
 */
void clean_up();

/**
 * Performs cleanup and exits the program with the specified status code.
 *
 * @param status The exit status code.
 */
void shutdown(int status);

/**
 * Prints an error message for a missing filename argument and usage instructions, then exits.
 *
 * @param programname The name of the executable program.
 */
void missing_filename_error(const char *programname);

/**
 * Prints an error message when memory allocation fails for a specified variable, then exits.
 *
 * @param variable_name The name of the variable for which memory allocation failed.
 */
void unable_to_allocate_memory_error(const char *variable_name);

/**
 * Frees the memory pointed to by `ptr` if it's not NULL and sets the pointer to NULL.
 *
 * Note: Only the pointer itself is set to NULL locally, so this has no effect on caller's pointer.
 *
 * @param ptr Pointer to the memory block to free.
 */
void free_and_null(void *ptr);

/**
 * Prints an error message for unrecognized assembly syntax at a specific line, then exits.
 *
 * @param line The offending line from the source file.
 * @param line_number The line number in the source file.
 */
void unrecognized_assembly_syntax_error(const char *line, int line_number);

/**
 * Prints an error message for an invalid instruction and exits.
 *
 * @param instruction A NULL-terminated array of token strings representing the instruction.
 */
void invalid_instruction_error(char **instruction);

/**
 * Prints a segmentation fault error message with context and exits.
 *
 * @param error_msg Additional error message or context about the fault.
 */
void segmentation_fault_error(const char *error_msg);

/**
 * Prints an error message when a file cannot be opened, then exits.
 *
 * @param file The name/path of the file that could not be opened.
 */
void could_not_open_file(const char *file);

/**
 * Prints an error message for an unrecognized opcode and optionally suggests an alternative, then exits.
 *
 * @param instruction A NULL-terminated array of token strings representing the instruction.
 * @param alt Optional suggested alternative opcode string, or NULL if none.
 */
void unknown_opcode_error(char **instruction, const char *alt);

/**
 * Prints a "not implemented" error message with file and line info and additional message, then exits.
 *
 * @param file The filename where the not implemented code was encountered.
 * @param line The line number of the not implemented code.
 * @param msg Optional additional message to provide context, or NULL.
 */
void not_implemented_error(const char *file, const int line, const char *msg);


#endif