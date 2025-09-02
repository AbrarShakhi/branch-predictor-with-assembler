#ifndef ARGS_H
#define ARGS_H

/**
 * Parses command-line arguments to obtain a file path.
 *
 * If the first argument is an option starting with '-':
 *   - If the option is "-e" and followed by another argument, the file path
 *     is constructed by prepending "./example/" to the second argument.
 *   - Otherwise, a missing filename error is raised.
 * If the first argument is not an option, it is treated as the file path
 * directly.
 *
 * The returned file path is dynamically allocated and must be freed by the
 * caller.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return A dynamically allocated string containing the parsed file path.
 * @throws Calls missing_filename_error if a filename argument is missing.
 * @throws Calls unable_to_allocate_memory_error if memory allocation fails.
 */
char *parse_args(const int argc, char *argv[]);

#endif