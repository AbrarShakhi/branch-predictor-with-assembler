#include "miscs.h"

#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "cpu.h"
#include "stb_ds.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#endif

int my_getch() {
#ifdef _WIN32
  return getch();
#else
  struct termios old, new;
  int ch;

  tcgetattr(STDIN_FILENO, &old);
  new = old;
  new.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &old);
  return ch;
#endif
}

void clean_up() {
  extern Cpu *cpu;
  extern Assembler *assembler;

  cpu_destroy(cpu);
  assembler_destroy(assembler);
}

void shutdown(int status) {
  clean_up();
  exit(status);
}

void missing_filename_error(const char *programname) {
  fprintf(stderr, RED BOLD "Error: " RESET RED "File name required!\n" RESET);
  fprintf(stderr, CYAN "Use Case:\n" RESET);
  fprintf(stderr, "\t" GREEN "%s" RESET " [your assembly file]\n\n",
          programname);
  fprintf(stderr, CYAN "Example:\n" RESET);
  fprintf(stderr, "\t" GREEN "%s" RESET " " YELLOW "asmbly.s\n\n" RESET,
          programname);

  fprintf(
      stderr, BLUE
      "If you unsure what assembly code to pass use our own defined\n" RESET);
  fprintf(stderr,
          "\t" GREEN "%s" RESET " " MAGENTA "-e" RESET " " YELLOW
          "%s\n\n" RESET,
          programname, "ifelse.s");
  fprintf(stderr, DIM
          "you can use other assembly located in example directory.\n" RESET);

  shutdown(-1);
}

void unable_to_allocate_memory_error(const char *variable_name) {
  fprintf(stderr,
          RED BOLD "Memory Error: " RESET RED
                   "Unable to allocate memory [" YELLOW "%s" RED "]\n" RESET,
          variable_name);
  shutdown(-1);
}

void free_and_null(void *ptr) {
  if (ptr) {
    free(ptr);
  }
  ptr = NULL;
}

void unrecognized_assembly_syntax_error(const char *line, int line_number) {
  fprintf(stderr, RED BOLD "Syntax Error: " RESET RED
                           "unrecognized assembly syntax.\n" RESET);
  fprintf(stderr, YELLOW "line number: " RESET BOLD "%d\n" RESET, line_number);
  fprintf(stderr, RED ">> " RESET BOLD "%s\n" RESET, line);
  shutdown(-1);
}

void invalid_instruction_error(char **instruction) {
  fprintf(stderr, RED BOLD "\nInvalid Instruction: " RESET);
  for (int i = 0; i < arrlen(instruction); i++) {
    fprintf(stderr, YELLOW "%s " RESET, instruction[i]);
  }
  fprintf(stderr, RED "\n__^^^__ Bad instructions.\n" RESET);
  shutdown(-1);
}

void segmentation_fault_error(const char *error_msg) {
  fprintf(stderr,
          RED BOLD "Segmentation Fault: " RESET RED
                   "occurred when executing your assembly: " YELLOW
                   "%s\n" RESET,
          error_msg);
  shutdown(-1);
}

void could_not_open_file(const char *file) {
  fprintf(stderr,
          RED BOLD "File Error: " RESET RED "Could not open: " YELLOW
                   "%s\n" RESET,
          file);
  shutdown(-1);
}

void unknown_opcode_error(char **instruction, const char *alt) {
  fprintf(stderr, RED BOLD "\nOpcode Error: " RESET);
  for (int i = 0; i < arrlen(instruction); i++) {
    fprintf(stderr, YELLOW "%s " RESET, instruction[i]);
  }
  fprintf(stderr, RED "\n__^^^__ Unrecognized opcode.\n" RESET);
  if (alt) {
    fprintf(stderr, GREEN "Did you mean: " CYAN "%s\n" RESET, alt);
  }
  shutdown(-1);
}

void not_implemented_error(const char *file, const int line, const char *msg) {
  fprintf(stderr, MAGENTA BOLD "NOT IMPLEMENTED CODE: \n" RESET);
  fprintf(stderr, CYAN "FILE: " RESET YELLOW "%s\n" RESET, file);
  fprintf(stderr, CYAN "LINE: " RESET YELLOW "%d\n" RESET, line);
  if (msg) {
    fprintf(stderr, WHITE "%s\n" RESET, msg);
  }
  shutdown(-1);
}