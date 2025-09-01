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


int my_getch();
void clean_up();
void shutdown(int);
void missing_filename_error(const char *);
void free_and_null(void *ptr);
void unable_to_allocate_memory_error(const char *);
void unrecognized_assembly_syntax_error(const char *, int);
void invalid_instruction_error(char **instructions);
void could_not_open_file(const char *);
void segmentation_fault_error(const char *);
void unknown_opcode_error(char **, const char *);
void not_implemented_error(const char *, const int, const char *);

#endif