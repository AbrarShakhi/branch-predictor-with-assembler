#ifndef UTILS_H
#define UTILS_H

void missing_filename_error();
void free_and_null(void *ptr);
void unable_to_allocate_memory_error(const char *);
void unrecognized_assembly_syntax_error(const char *, int);
void invalid_instruction_error(char **instructions);
void could_not_open_file(const char *);
void segmentation_fault_error(const char *);
void unknown_opcode_error(char **, const char *);

#endif