#ifndef UTILS_H
#define UTILS_H

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