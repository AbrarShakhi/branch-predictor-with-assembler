#ifndef READER_H
#define READER_H


char **read_assembly(const char *file);
void unable_to_allocate_memory_error(char *);
void free_and_null(void *);

#endif