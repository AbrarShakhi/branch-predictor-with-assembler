#ifndef READER_H
#define READER_H

#include <stdio.h>

/**
 * Reads a single line from the specified file stream.
 *
 * Dynamically allocates a buffer to store the line read from `stream`.
 * The buffer grows as needed to accommodate lines of arbitrary length.
 * The returned string is null-terminated and **must be freed** by the caller.
 *
 * @param stream The input file stream to read from.
 * @return A dynamically allocated string containing the line read (without
 * newline), or NULL if end-of-file is reached immediately or on memory
 * allocation failure.
 */
char *read_line(FILE *stream);

/**
 * Reads all lines from the specified assembly source file.
 *
 * Opens the specified file for reading, reads all lines using `read_line()`,
 * and stores pointers to each line in a dynamically growing array.
 * The array and the individual line strings **must be freed** by the caller
 * when no longer needed.
 *
 * @param file The path to the assembly source file to read.
 * @return A NULL-terminated dynamically allocated array of strings, each
 * corresponding to one line of the file. Calls `could_not_open_file(file)` and
 * terminates if the file cannot be opened.
 */
char **read_assembly(const char *file);

#endif